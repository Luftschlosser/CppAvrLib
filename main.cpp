#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/periphery/Pin.h"
#include "src/resources/periphery/Usart.h"

#include "src/resources/Interrupts.h"


char __attribute__ ((noinline)) x() {
	return 'B';
}

void callback() {
	//do something
}

int main (void) noexcept
{

	Usart& usart = Periphery::usart0;
	InterruptSource* rxIrq = usart.accessRxInterruptSource();
	rxIrq->registerCallback(&callback);

	//Pin led(Periphery::portB, 6);
	//Pin led(Periphery::getInstance<Port>(x()), 6);
	const Pin led(Periphery::getInstance<Port>('B'), 6);

	led.init();
	led.setMode(Pin::Mode::OUTPUT);

    // Main-loop
    while (1)
    {
        led.toggle();
        _delay_ms(500);
    }
}
