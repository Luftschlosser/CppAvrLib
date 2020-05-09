#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/periphery/Pin.h"
#include "src/resources/periphery/Usart.h"

#include "src/resources/Interrupts.h"

const Pin led(Periphery::getInstance<Port>('B'), 6);

void on() {
	led.setHigh();
}

class Off final : public Listener {
private:
	const Pin& pin;
public:
	inline Off(const Pin& pin) : pin(pin) {}
	virtual void trigger() noexcept {
		pin.setLow();
	}
};

int main (void) noexcept
{
	/*
	Usart& usart = Periphery::usart0;
	EventSource& rxIrq = usart.accessRxInterruptSource();
	rxIrq.registerCallback(&on);*/

	//Testing callback
	Interrupt irq1 = Interrupt::Create<1>();
	irq1.registerCallback(&on);

	//Testing Listener
	Off off(led);
	Interrupt irq2 = Interrupt::Create<2>();
	irq2.registerListener(off);

	led.init();
	led.setMode(Pin::Mode::OUTPUT);

    // Main-loop
    while (1)
    {
    	Interrupt::invoke<1>();
        _delay_ms(500);
        Interrupt::invoke<2>();
        _delay_ms(500);
    }
}
