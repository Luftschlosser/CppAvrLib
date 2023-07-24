#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/Interrupts.h"


const Pin led = Periphery::getPin<'B', 6>();
Timer16bit& timer = Periphery::getTimer16bit<5>();

class Log final {
private:
	Usart& usart;
	volatile bool ready;
	const char* msg;

	inline void dataRegisterEmptyTrigger() noexcept {
		if (*++msg != 0) {
			usart.write(*msg);
		}
		else {
			usart.disableDataRegisterEmptyInterrupt();
			while (!usart.isTransmitComplete());
			usart.clearTransmitComplete();
			ready = true;
		}
	}
public:
	inline Log(Usart& usart, Interrupt udre) noexcept : usart(usart), ready (true), msg(nullptr) {
		usart.init();
		usart.regUBRR = 103; //Baud 9600 @ 16MHz
		usart.regUCSRC.reg = 3 << 1; //Async,No Parity,1 Stopbit,8 bit character size
		udre.registerMethod<Log, &Log::dataRegisterEmptyTrigger>(*this);
		usart.enableTransmitter();
	}

	inline ~Log() {}

	inline void write(const char* s) noexcept {
		if (*s != 0){
			while (!ready);
			ready = false;
			msg = s;
			usart.enableDataRegisterEmptyInterrupt();
			usart.write(*msg);
		}
	}

	inline void write(const char c) noexcept {
		while (!ready);
		usart.write(c);
		while (!usart.isTransmitComplete());
		usart.clearTransmitComplete();
	}

	inline void write(uint8_t num) noexcept {
		write(static_cast<char>((num / 100) + '0'));
		write(static_cast<char>(((num % 100) / 10) + '0'));
		write(static_cast<char>((num % 10) + '0'));
	}

	inline void writeBinary(uint8_t num) noexcept {
		for (int8_t x = 7; x >= 0; x--) {
			write(static_cast<char>(((num >> x) & 1) + '0'));
		}
	}
};

void toggle() {
	led.toggle();
}

void incPwm() {
	static uint8_t value = 0;
	value++;
	timer.setOutputCompareValue<'A'>((uint16_t)value);
	timer.setOutputCompareValue<'B'>((uint16_t)value);
}

int main (void) noexcept
{
	sei();

	Log log(Periphery::getUsart<0>(), Interrupts::getUsartUdreInterrupt<0>());
	led.init();
	led.setMode(Pin::Mode::OUTPUT);

	timer.init();
	Interrupt tov = Interrupts::getTimerOvfInterrupt<5>();
	tov.registerFunction<&incPwm>();
	timer.enableTimerOverflowInterrupt();
	timer.setWaveformGenerationMode(Timer16bit::WaveformGenerationMode::PWM_FAST_0X00FF);
	timer.setOutputCompareValue<'A'>(5);
	timer.setOutputCompareValue<'B'>(5);
	timer.setCompareOutputMode<'A'>(Timer16bit::CompareOutputMode::CLEAR);
	timer.setCompareOutputMode<'B'>(Timer16bit::CompareOutputMode::SET);
	timer.setClockSelect(Timer16bit::ClockSelect::PRESCALE_256);

    // Main-loop
    while (1)
    {
    	_delay_ms(500);
		led.setHigh();
		log.write("\n\rHello");
		_delay_ms(500);
		led.setLow();
    }
}
