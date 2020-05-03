#include <util/delay.h>

#include "src/resources/Periphery.h"
#include "src/resources/periphery/Pin.h"

using namespace Periphery;

int main (void) noexcept
{
	Pin led(portB, 6);

	led.setOutput();

    // Main-loop
    while (1)
    {
        led.toggle();
        _delay_ms(500);
    }
}
