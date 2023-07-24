#include <avr/interrupt.h>
#include "../Configuration.h"
#include "../interrupts/Interrupt.h"


//ISR-Routine (enabled)	: 98B ROM + 4B RAM
//ISR-Routine (empty)	: 20B ROM + 0B RAM


//_____________________________________________
//INTERRUPT-CONFIGURATION:2

//Implementation Type configuration for each Interrupt source [ISR_NAKED / ISR_BLOCK / ISR_NOBLOCK] (Comment out #define to omit ISR-Routine completely)
#define ISRTYPE_EXT_INT0 	ISR_BLOCK
#define ISRTYPE_EXT_INT1 	ISR_BLOCK
#define ISRTYPE_EXT_INT2 	ISR_BLOCK
#define ISRTYPE_EXT_INT3 	ISR_BLOCK
#define ISRTYPE_EXT_INT4 	ISR_BLOCK
#define ISRTYPE_EXT_INT5 	ISR_BLOCK
#define ISRTYPE_EXT_INT6 	ISR_BLOCK
#define ISRTYPE_EXT_INT7 	ISR_BLOCK

#define ISRTYPE_PCINT0		ISR_BLOCK
#define ISRTYPE_PCINT1		ISR_BLOCK
#define ISRTYPE_PCINT2		ISR_BLOCK

#define ISRTYPE_USART0_RX 	ISR_BLOCK
#define ISRTYPE_USART0_TX 	ISR_BLOCK
#define ISRTYPE_USART0_UDRE	ISR_BLOCK
#define ISRTYPE_USART1_RX 	ISR_BLOCK
#define ISRTYPE_USART1_TX 	ISR_BLOCK
#define ISRTYPE_USART1_UDRE	ISR_BLOCK
#define ISRTYPE_USART2_RX 	ISR_BLOCK
#define ISRTYPE_USART2_TX 	ISR_BLOCK
#define ISRTYPE_USART2_UDRE	ISR_BLOCK
#define ISRTYPE_USART3_RX 	ISR_BLOCK
#define ISRTYPE_USART3_TX 	ISR_BLOCK
#define ISRTYPE_USART3_UDRE	ISR_BLOCK

#define ISRTYPE_TIMER0_OCA	ISR_BLOCK
#define ISRTYPE_TIMER0_OCB	ISR_BLOCK
#define ISRTYPE_TIMER0_OVF	ISR_BLOCK
#define ISRTYPE_TIMER1_OCA	ISR_BLOCK
#define ISRTYPE_TIMER1_OCB	ISR_BLOCK
#define ISRTYPE_TIMER1_OCC	ISR_BLOCK
#define ISRTYPE_TIMER1_OVF	ISR_BLOCK
#define ISRTYPE_TIMER1_CAPT	ISR_BLOCK
#define ISRTYPE_TIMER2_OCA	ISR_BLOCK
#define ISRTYPE_TIMER2_OCB	ISR_BLOCK
#define ISRTYPE_TIMER2_OVF	ISR_BLOCK
#define ISRTYPE_TIMER3_OCA	ISR_BLOCK
#define ISRTYPE_TIMER3_OCB	ISR_BLOCK
#define ISRTYPE_TIMER3_OCC	ISR_BLOCK
#define ISRTYPE_TIMER3_OVF	ISR_BLOCK
#define ISRTYPE_TIMER3_CAPT	ISR_BLOCK
#define ISRTYPE_TIMER4_OCA	ISR_BLOCK
#define ISRTYPE_TIMER4_OCB	ISR_BLOCK
#define ISRTYPE_TIMER4_OCC	ISR_BLOCK
#define ISRTYPE_TIMER4_OVF	ISR_BLOCK
#define ISRTYPE_TIMER4_CAPT	ISR_BLOCK
#define ISRTYPE_TIMER5_OCA	ISR_BLOCK
#define ISRTYPE_TIMER5_OCB	ISR_BLOCK
#define ISRTYPE_TIMER5_OCC	ISR_BLOCK
#define ISRTYPE_TIMER5_OVF	ISR_BLOCK
#define ISRTYPE_TIMER5_CAPT	ISR_BLOCK


//___________________________________
//External Interrupts

#ifdef ISRTYPE_EXT_INT0
ISR(INT0_vect, ISRTYPE_EXT_INT0) {
	if (Configuration::enableInterrupt_EXT_INT0)
		Interrupt::invoke<INT0_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT1
ISR(INT1_vect, ISRTYPE_EXT_INT1) {
	if (Configuration::enableInterrupt_EXT_INT1)
		Interrupt::invoke<INT1_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT2
ISR(INT2_vect, ISRTYPE_EXT_INT2) {
	if (Configuration::enableInterrupt_EXT_INT2)
		Interrupt::invoke<INT2_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT3
ISR(INT3_vect, ISRTYPE_EXT_INT3) {
	if (Configuration::enableInterrupt_EXT_INT3)
		Interrupt::invoke<INT3_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT4
ISR(INT4_vect, ISRTYPE_EXT_INT4) {
	if (Configuration::enableInterrupt_EXT_INT4)
		Interrupt::invoke<INT4_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT5
ISR(INT5_vect, ISRTYPE_EXT_INT5) {
	if (Configuration::enableInterrupt_EXT_INT5)
		Interrupt::invoke<INT5_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT6
ISR(INT6_vect, ISRTYPE_EXT_INT6) {
	if (Configuration::enableInterrupt_EXT_INT6)
		Interrupt::invoke<INT6_vect_num>();
}
#endif

#ifdef ISRTYPE_EXT_INT7
ISR(INT7_vect, ISRTYPE_EXT_INT7) {
	if (Configuration::enableInterrupt_EXT_INT7)
		Interrupt::invoke<INT7_vect_num>();
}
#endif

//___________________________________
//PinChange Interrupts

#ifdef ISRTYPE_PCINT0
ISR(PCINT0_vect, ISRTYPE_PCINT0) {
	if (Configuration::enableInterrupt_PCINT0)
		Interrupt::invoke<PCINT0_vect_num>();
}
#endif

#ifdef ISRTYPE_PCINT1
ISR(PCINT1_vect, ISRTYPE_PCINT1) {
	if (Configuration::enableInterrupt_PCINT1)
		Interrupt::invoke<PCINT1_vect_num>();
}
#endif

#ifdef ISRTYPE_PCINT2
ISR(PCINT2_vect, ISRTYPE_PCINT2) {
	if (Configuration::enableInterrupt_PCINT2)
		Interrupt::invoke<PCINT2_vect_num>();
}
#endif

//___________________________________
//Usart RX

//USART0_RX
#ifdef ISRTYPE_USART0_RX
ISR(USART0_RX_vect, ISRTYPE_USART0_RX) {
	if (Configuration::enableInterrupt_USART0_RX)
		Interrupt::invoke<USART0_RX_vect_num>();
}
#endif

//USART1_RX
#ifdef ISRTYPE_USART1_RX
ISR(USART1_RX_vect, ISRTYPE_USART1_RX) {
	if (Configuration::enableInterrupt_USART1_RX)
		Interrupt::invoke<USART1_RX_vect_num>();
}
#endif

//USART2_RX
#ifdef ISRTYPE_USART2_RX
ISR(USART2_RX_vect, ISRTYPE_USART2_RX) {
	if (Configuration::enableInterrupt_USART2_RX)
		Interrupt::invoke<USART2_RX_vect_num>();
}
#endif

//USART3_RX
#ifdef ISRTYPE_USART3_RX
ISR(USART3_RX_vect, ISRTYPE_USART3_RX) {
	if (Configuration::enableInterrupt_USART3_RX)
		Interrupt::invoke<USART3_RX_vect_num>();
}
#endif

//___________________________________
//Usart TX

//USART0_TX
#ifdef ISRTYPE_USART0_TX
ISR(USART0_TX_vect, ISRTYPE_USART0_TX) {
	if (Configuration::enableInterrupt_USART0_TX)
		Interrupt::invoke<USART0_TX_vect_num>();
}
#endif

//USART1_TX
#ifdef ISRTYPE_USART1_TX
ISR(USART1_TX_vect, ISRTYPE_USART1_TX) {
	if (Configuration::enableInterrupt_USART1_TX)
		Interrupt::invoke<USART1_TX_vect_num>();
}
#endif

//USART2_TX
#ifdef ISRTYPE_USART2_TX
ISR(USART2_TX_vect, ISRTYPE_USART2_TX) {
	if (Configuration::enableInterrupt_USART2_TX)
		Interrupt::invoke<USART2_TX_vect_num>();
}
#endif

//USART3_TX
#ifdef ISRTYPE_USART3_TX
ISR(USART3_TX_vect, ISRTYPE_USART3_TX) {
	if (Configuration::enableInterrupt_USART3_TX)
		Interrupt::invoke<USART3_TX_vect_num>();
}
#endif

//___________________________________
//Usart UDRE

//USART0_UDRE
#ifdef ISRTYPE_USART0_UDRE
ISR(USART0_UDRE_vect, ISRTYPE_USART0_UDRE) {
	if (Configuration::enableInterrupt_USART0_UDRE)
		Interrupt::invoke<USART0_UDRE_vect_num>();
}
#endif

//USART1_UDRE
#ifdef ISRTYPE_USART1_UDRE
ISR(USART1_UDRE_vect, ISRTYPE_USART1_UDRE) {
	if (Configuration::enableInterrupt_USART1_UDRE)
		Interrupt::invoke<USART1_UDRE_vect_num>();
}
#endif

//USART2_UDRE
#ifdef ISRTYPE_USART2_UDRE
ISR(USART2_UDRE_vect, ISRTYPE_USART2_UDRE) {
	if (Configuration::enableInterrupt_USART2_UDRE)
		Interrupt::invoke<USART2_UDRE_vect_num>();
}
#endif

//USART3_UDRE
#ifdef ISRTYPE_USART3_UDRE
ISR(USART3_UDRE_vect, ISRTYPE_USART3_UDRE) {
	if (Configuration::enableInterrupt_USART3_UDRE)
		Interrupt::invoke<USART3_UDRE_vect_num>();
}
#endif

//___________________________________
//Timer	OC

//TIMER0 OCA
#ifdef ISRTYPE_TIMER0_OCA
ISR(TIMER0_COMPA_vect, ISRTYPE_TIMER0_OCA) {
	if (Configuration::enableInterrupt_TIMER0_OC_A)
		Interrupt::invoke<TIMER0_COMPA_vect_num>();
}
#endif

//TIMER0 OCB
#ifdef ISRTYPE_TIMER0_OCB
ISR(TIMER0_COMPB_vect, ISRTYPE_TIMER0_OCB) {
	if (Configuration::enableInterrupt_TIMER0_OC_B)
		Interrupt::invoke<TIMER0_COMPB_vect_num>();
}
#endif

//TIMER1 OCA
#ifdef ISRTYPE_TIMER1_OCA
ISR(TIMER1_COMPA_vect, ISRTYPE_TIMER1_OCA) {
	if (Configuration::enableInterrupt_TIMER1_OC_A)
		Interrupt::invoke<TIMER1_COMPA_vect_num>();
}
#endif

//TIMER1 OCB
#ifdef ISRTYPE_TIMER1_OCB
ISR(TIMER1_COMPB_vect, ISRTYPE_TIMER1_OCB) {
	if (Configuration::enableInterrupt_TIMER1_OC_B)
		Interrupt::invoke<TIMER1_COMPB_vect_num>();
}
#endif

//TIMER1 OCC
#ifdef ISRTYPE_TIMER1_OCC
ISR(TIMER1_COMPC_vect, ISRTYPE_TIMER1_OCC) {
	if (Configuration::enableInterrupt_TIMER1_OC_C)
		Interrupt::invoke<TIMER1_COMPC_vect_num>();
}
#endif

//TIMER2 OCA
#ifdef ISRTYPE_TIMER2_OCA
ISR(TIMER2_COMPA_vect, ISRTYPE_TIMER2_OCA) {
	if (Configuration::enableInterrupt_TIMER2_OC_A)
		Interrupt::invoke<TIMER2_COMPA_vect_num>();
}
#endif

//TIMER2 OCB
#ifdef ISRTYPE_TIMER2_OCB
ISR(TIMER2_COMPB_vect, ISRTYPE_TIMER2_OCB) {
	if (Configuration::enableInterrupt_TIMER2_OC_B)
		Interrupt::invoke<TIMER2_COMPB_vect_num>();
}
#endif

//TIMER3 OCA
#ifdef ISRTYPE_TIMER3_OCA
ISR(TIMER3_COMPA_vect, ISRTYPE_TIMER3_OCA) {
	if (Configuration::enableInterrupt_TIMER3_OC_A)
		Interrupt::invoke<TIMER3_COMPA_vect_num>();
}
#endif

//TIMER3 OCB
#ifdef ISRTYPE_TIMER3_OCB
ISR(TIMER3_COMPB_vect, ISRTYPE_TIMER3_OCB) {
	if (Configuration::enableInterrupt_TIMER3_OC_B)
		Interrupt::invoke<TIMER3_COMPB_vect_num>();
}
#endif

//TIMER3 OCC
#ifdef ISRTYPE_TIMER3_OCC
ISR(TIMER3_COMPC_vect, ISRTYPE_TIMER3_OCC) {
	if (Configuration::enableInterrupt_TIMER3_OC_C)
		Interrupt::invoke<TIMER3_COMPC_vect_num>();
}
#endif

//TIMER4 OCA
#ifdef ISRTYPE_TIMER4_OCA
ISR(TIMER4_COMPA_vect, ISRTYPE_TIMER4_OCA) {
	if (Configuration::enableInterrupt_TIMER4_OC_A)
		Interrupt::invoke<TIMER4_COMPA_vect_num>();
}
#endif

//TIMER4 OCB
#ifdef ISRTYPE_TIMER4_OCB
ISR(TIMER4_COMPB_vect, ISRTYPE_TIMER4_OCB) {
	if (Configuration::enableInterrupt_TIMER4_OC_B)
		Interrupt::invoke<TIMER4_COMPB_vect_num>();
}
#endif

//TIMER4 OCC
#ifdef ISRTYPE_TIMER4_OCC
ISR(TIMER4_COMPC_vect, ISRTYPE_TIMER4_OCC) {
	if (Configuration::enableInterrupt_TIMER4_OC_C)
		Interrupt::invoke<TIMER4_COMPC_vect_num>();
}
#endif

//TIMER5 OCA
#ifdef ISRTYPE_TIMER5_OCA
ISR(TIMER5_COMPA_vect, ISRTYPE_TIMER5_OCA) {
	if (Configuration::enableInterrupt_TIMER5_OC_A)
		Interrupt::invoke<TIMER5_COMPA_vect_num>();
}
#endif

//TIMER5 OCB
#ifdef ISRTYPE_TIMER5_OCB
ISR(TIMER5_COMPB_vect, ISRTYPE_TIMER5_OCB) {
	if (Configuration::enableInterrupt_TIMER5_OC_B)
		Interrupt::invoke<TIMER5_COMPB_vect_num>();
}
#endif

//TIMER5 OCC
#ifdef ISRTYPE_TIMER5_OCC
ISR(TIMER5_COMPC_vect, ISRTYPE_TIMER5_OCC) {
	if (Configuration::enableInterrupt_TIMER5_OC_C)
		Interrupt::invoke<TIMER5_COMPC_vect_num>();
}
#endif

//___________________________________
//Timer	OVF

//TIMER0 OVF
#ifdef ISRTYPE_TIMER0_OVF
ISR(TIMER0_OVF_vect, ISRTYPE_TIMER0_OVF) {
	if (Configuration::enableInterrupt_TIMER0_OVF)
		Interrupt::invoke<TIMER0_OVF_vect_num>();
}
#endif

//TIMER1 OVF
#ifdef ISRTYPE_TIMER1_OVF
ISR(TIMER1_OVF_vect, ISRTYPE_TIMER1_OVF) {
	if (Configuration::enableInterrupt_TIMER1_OVF)
		Interrupt::invoke<TIMER1_OVF_vect_num>();
}
#endif

//TIMER2 OVF
#ifdef ISRTYPE_TIMER2_OVF
ISR(TIMER2_OVF_vect, ISRTYPE_TIMER2_OVF) {
	if (Configuration::enableInterrupt_TIMER2_OVF)
		Interrupt::invoke<TIMER2_OVF_vect_num>();
}
#endif

//TIMER3 OVF
#ifdef ISRTYPE_TIMER3_OVF
ISR(TIMER3_OVF_vect, ISRTYPE_TIMER3_OVF) {
	if (Configuration::enableInterrupt_TIMER3_OVF)
		Interrupt::invoke<TIMER3_OVF_vect_num>();
}
#endif

//TIMER4 OVF
#ifdef ISRTYPE_TIMER4_OVF
ISR(TIMER4_OVF_vect, ISRTYPE_TIMER4_OVF) {
	if (Configuration::enableInterrupt_TIMER4_OVF)
		Interrupt::invoke<TIMER4_OVF_vect_num>();
}
#endif

//TIMER5 OVF
#ifdef ISRTYPE_TIMER5_OVF
ISR(TIMER5_OVF_vect, ISRTYPE_TIMER5_OVF) {
	if (Configuration::enableInterrupt_TIMER5_OVF)
		Interrupt::invoke<TIMER5_OVF_vect_num>();
}
#endif

//___________________________________
//Timer	CAPT

//TIMER1 CAPT
#ifdef ISRTYPE_TIMER1_CAPT
ISR(TIMER1_CAPT_vect, ISRTYPE_TIMER1_CAPT) {
	if (Configuration::enableInterrupt_TIMER1_CAPT)
		Interrupt::invoke<TIMER1_CAPT_vect_num>();
}
#endif

//TIMER3 CAPT
#ifdef ISRTYPE_TIMER3_CAPT
ISR(TIMER3_CAPT_vect, ISRTYPE_TIMER3_CAPT) {
	if (Configuration::enableInterrupt_TIMER3_CAPT)
		Interrupt::invoke<TIMER3_CAPT_vect_num>();
}
#endif

//TIMER4 CAPT
#ifdef ISRTYPE_TIMER4_CAPT
ISR(TIMER4_CAPT_vect, ISRTYPE_TIMER4_CAPT) {
	if (Configuration::enableInterrupt_TIMER4_CAPT)
		Interrupt::invoke<TIMER4_CAPT_vect_num>();
}
#endif

//TIMER5 CAPT
#ifdef ISRTYPE_TIMER5_CAPT
ISR(TIMER5_CAPT_vect, ISRTYPE_TIMER5_CAPT) {
	if (Configuration::enableInterrupt_TIMER5_CAPT)
		Interrupt::invoke<TIMER5_CAPT_vect_num>();
}
#endif
