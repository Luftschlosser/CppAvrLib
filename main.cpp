#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/Interrupts.h"

const Pin led = Periphery::getPin<'B', 6>();
const Timer8bit timer = Periphery::getTimer8bit<0>();

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
		led.setLow();
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
	timer.setOutputCompareValue<'A'>(value);
	timer.setOutputCompareValue<'B'>(0xFF-value);
}

int main (void) noexcept
{
	sei();
	Log log(Periphery::getUsart<0>(), Interrupts::getUsartUdreInterrupt<0>());

	led.init();
	led.setMode(Pin::Mode::OUTPUT);
	led.setHigh();

	InterruptPin t = Periphery::getInterruptPin<0>();
	t.init();
	t.setMode(Pin::Mode::INPUT);
	t.setInterruptMode(InterruptPin::InterruptSenseMode::TOGGLE);
	Interrupts::getExternalInterrupt<0>().registerFunction<&toggle>();
	t.enableInterrupt();

	timer.init();
	Interrupt tov = Interrupts::getTimerOvfInterrupt<0>();
	tov.registerFunction<&incPwm>();
	timer.enableTimerOverflowInterrupt();
	timer.setWaveformGenerationMode(Timer8bit::WaveformGenerationMode::PWM_FAST_0XFF);
	timer.setOutputCompareValue<'A'>(0);
	timer.setOutputCompareValue<'B'>(0);
	timer.setCompareOutputMode<'A'>(Timer8bit::CompareOutputMode::CLEAR);
	timer.setCompareOutputMode<'B'>(Timer8bit::CompareOutputMode::CLEAR);
	timer.setClockSelect(Timer8bit::ClockSelect::PRESCALE_1024);

    // Main-loop
    while (1)
    {
    	/*
		_delay_ms(500);
		led.setHigh();
		log.write("\r\nHello World!");
		_delay_ms(500);
		led.setLow();
		*/
    }
}
