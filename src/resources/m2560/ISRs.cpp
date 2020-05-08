#include <avr/interrupt.h>
#include "../interrupts/InterruptConfiguration.h"
#include "../interrupts/Interrupt.h"

#if ISRTYPE_USART0_RX != NONE
#if ISRTYPE_USART0_RX == BLOCK

ISR(USART0_RX_vect, ISR_BLOCK) {
	Interrupt::invoke(USART0_RX_vect_num);
}

#elif ISRTYPE_USART0_RX == NOBLOCK

ISR(USART0_RX_vect, ISR_NOBLOCK) {
	Interrupt::invoke(USART0_RX_vect_num);
}

#endif
#endif
