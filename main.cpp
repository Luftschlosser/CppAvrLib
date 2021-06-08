#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/periphery/Pin.h"
#include "src/resources/periphery/Usart.h"
#include "src/resources/periphery/InterruptPin.h"

#include "src/resources/Interrupts.h"

const Pin led(Periphery::getInstance<Port, 'B'>(), 6);

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
	inline Log(Usart& usart) noexcept : usart(usart), ready (true), msg(nullptr) {
		usart.init();
		usart.regUBRR = 103; //Baud 9600 @ 16MHz
		usart.regUCSRC.reg = 3 << 1; //Async,No Parity,1 Stopbit,8 bit character size
		usart.accessDataRegisterEmptyInterrupt().registerMethod<Log, &Log::dataRegisterEmptyTrigger>(*this);
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
	_delay_ms(1000);
}

int main (void) noexcept
{
	sei();
	Log log(Periphery::getInstance<Usart, 0>());

	led.init();
	led.setMode(Pin::Mode::OUTPUT);
	led.setHigh();

	InterruptPin& t = Periphery::getInstance<InterruptPin, 0>();
	t.init();
	t.setMode(Pin::Mode::INPUT);
	t.setInterruptMode(InterruptPin::InterruptSenseMode::TOGGLE);
	t.accessInterrupt().registerFunction<&toggle>();
	t.enableInterrupt();

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
