#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/periphery/Pin.h"


char __attribute__ ((noinline)) x() {
	return 'B';
}

int main (void) noexcept
{
	//Pin led(*Periphery::portB, 6);
	//Pin led(Periphery::getInstance<Port>(x()), 6);
	Pin led(Periphery::getInstance<Port>('B'), 6);

	led.init();
	led.setOutput();

    // Main-loop
    while (1)
    {
        //led.toggleOutput();
        led.toggle();
        _delay_ms(500);
    }
}
