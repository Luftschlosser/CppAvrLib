#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/periphery/Pin.h"


int main (void) noexcept
{
	//Pin led(Periphery::portB, 6);
	Pin led(Periphery::getInstance<Port>('B'), 6);

	led.setOutput();

    // Main-loop
    while (1)
    {
        led.toggle();
        _delay_ms(500);
    }
}
