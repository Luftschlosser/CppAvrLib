#include <avr/interrupt.h>
#include "../Configuration.h"
#include "../interrupts/Interrupt.h"


//ISR-Routine (enabled)	: 98B ROM + 4B RAM
//ISR-Routine (empty)	: 20B ROM + 0B RAM


//_____________________________________________
//INTERRUPT-TYPES:

//Types of ISR-Routine-Implementations
#define NONE 	0
#define BLOCK 	1
#define NOBLOCK	2

//_____________________________________________
//INTERRUPT-CONFIGURATION:

//Implementation Type configuration for each Interrupt source [NONE / BLOCK / NOBLOCK]
#define ISRTYPE_EXT_INT0 	BLOCK
#define ISRTYPE_EXT_INT1 	BLOCK
#define ISRTYPE_EXT_INT2 	BLOCK
#define ISRTYPE_EXT_INT3 	BLOCK
#define ISRTYPE_EXT_INT4 	BLOCK
#define ISRTYPE_EXT_INT5 	BLOCK
#define ISRTYPE_EXT_INT6 	BLOCK
#define ISRTYPE_EXT_INT7 	BLOCK

#define ISRTYPE_USART0_RX 	BLOCK
#define ISRTYPE_USART0_TX 	BLOCK
#define ISRTYPE_USART0_UDRE	BLOCK
#define ISRTYPE_USART1_RX 	BLOCK
#define ISRTYPE_USART1_TX 	BLOCK
#define ISRTYPE_USART1_UDRE	BLOCK
#define ISRTYPE_USART2_RX 	BLOCK
#define ISRTYPE_USART2_TX 	BLOCK
#define ISRTYPE_USART2_UDRE	BLOCK
#define ISRTYPE_USART3_RX 	BLOCK
#define ISRTYPE_USART3_TX 	BLOCK
#define ISRTYPE_USART3_UDRE	BLOCK

#define ISRTYPE_TIMER0_OCA	BLOCK
#define ISRTYPE_TIMER0_OCB	BLOCK
#define ISRTYPE_TIMER0_OVF	BLOCK
#define ISRTYPE_TIMER2_OCA	BLOCK
#define ISRTYPE_TIMER2_OCB	BLOCK
#define ISRTYPE_TIMER2_OVF	BLOCK


//___________________________________
//External Interrupts

#if ISRTYPE_EXT_INT0 != NONE
#if ISRTYPE_EXT_INT0 == BLOCK

ISR(INT0_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT0)
		Interrupt::invoke<INT0_vect_num>();
}

#elif ISRTYPE_EXT_INT0 == NOBLOCK

ISR(INT0_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT0)
		Interrupt::invoke<INT0_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT1 != NONE
#if ISRTYPE_EXT_INT1 == BLOCK

ISR(INT1_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT1)
		Interrupt::invoke<INT1_vect_num>();
}

#elif ISRTYPE_EXT_INT1 == NOBLOCK

ISR(INT1_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT1)
		Interrupt::invoke<INT1_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT2 != NONE
#if ISRTYPE_EXT_INT2 == BLOCK

ISR(INT2_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT2)
		Interrupt::invoke<INT2_vect_num>();
}

#elif ISRTYPE_EXT_INT2 == NOBLOCK

ISR(INT2_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT2)
		Interrupt::invoke<INT2_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT3 != NONE
#if ISRTYPE_EXT_INT3 == BLOCK

ISR(INT3_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT3)
		Interrupt::invoke<INT3_vect_num>();
}

#elif ISRTYPE_EXT_INT3 == NOBLOCK

ISR(INT3_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT3)
		Interrupt::invoke<INT3_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT4 != NONE
#if ISRTYPE_EXT_INT4 == BLOCK

ISR(INT4_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT4)
		Interrupt::invoke<INT4_vect_num>();
}

#elif ISRTYPE_EXT_INT4 == NOBLOCK

ISR(INT4_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT4)
		Interrupt::invoke<INT4_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT5 != NONE
#if ISRTYPE_EXT_INT5 == BLOCK

ISR(INT5_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT5)
		Interrupt::invoke<INT5_vect_num>();
}

#elif ISRTYPE_EXT_INT5 == NOBLOCK

ISR(INT5_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT5)
		Interrupt::invoke<INT5_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT6 != NONE
#if ISRTYPE_EXT_INT6 == BLOCK

ISR(INT6_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT6)
		Interrupt::invoke<INT6_vect_num>();
}

#elif ISRTYPE_EXT_INT6 == NOBLOCK

ISR(INT6_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT6)
		Interrupt::invoke<INT6_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT7 != NONE
#if ISRTYPE_EXT_INT7 == BLOCK

ISR(INT7_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_EXT_INT7)
		Interrupt::invoke<INT7_vect_num>();
}

#elif ISRTYPE_EXT_INT7 == NOBLOCK

ISR(INT7_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_EXT_INT7)
		Interrupt::invoke<INT7_vect_num>();
}

#endif
#endif

//___________________________________
//Usart RX

//USART0_RX
#if ISRTYPE_USART0_RX != NONE
#if ISRTYPE_USART0_RX == BLOCK

ISR(USART0_RX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART0_RX)
		Interrupt::invoke<USART0_RX_vect_num>();
}

#elif ISRTYPE_USART0_RX == NOBLOCK

ISR(USART0_RX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART0_RX)
		Interrupt::invoke<USART0_RX_vect_num>();
}

#endif
#endif

//USART1_RX
#if ISRTYPE_USART1_RX != NONE
#if ISRTYPE_USART1_RX == BLOCK

ISR(USART1_RX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART1_RX)
		Interrupt::invoke<USART1_RX_vect_num>();
}

#elif ISRTYPE_USART1_RX == NOBLOCK

ISR(USART1_RX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART1_RX)
		Interrupt::invoke<USART1_RX_vect_num>();
}

#endif
#endif

//USART2_RX
#if ISRTYPE_USART2_RX != NONE
#if ISRTYPE_USART2_RX == BLOCK

ISR(USART2_RX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART2_RX)
		Interrupt::invoke<USART2_RX_vect_num>();
}

#elif ISRTYPE_USART2_RX == NOBLOCK

ISR(USART2_RX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART2_RX)
		Interrupt::invoke<USART2_RX_vect_num>();
}

#endif
#endif

//USART3_RX
#if ISRTYPE_USART3_RX != NONE
#if ISRTYPE_USART3_RX == BLOCK

ISR(USART3_RX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART3_RX)
		Interrupt::invoke<USART3_RX_vect_num>();
}

#elif ISRTYPE_USART3_RX == NOBLOCK

ISR(USART3_RX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART3_RX)
		Interrupt::invoke<USART3_RX_vect_num>();
}

#endif
#endif


//___________________________________
//Usart TX

//USART0_TX
#if ISRTYPE_USART0_TX != NONE
#if ISRTYPE_USART0_TX == BLOCK

ISR(USART0_TX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART0_TX)
		Interrupt::invoke<USART0_TX_vect_num>();
}

#elif ISRTYPE_USART0_TX == NOBLOCK

ISR(USART0_TX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART0_TX)
		Interrupt::invoke<USART0_TX_vect_num>();
}

#endif
#endif

//USART1_TX
#if ISRTYPE_USART1_TX != NONE
#if ISRTYPE_USART1_TX == BLOCK

ISR(USART1_TX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART1_TX)
		Interrupt::invoke<USART1_TX_vect_num>();
}

#elif ISRTYPE_USART1_TX == NOBLOCK

ISR(USART1_TX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART1_TX)
		Interrupt::invoke<USART1_TX_vect_num>();
}

#endif
#endif

//USART2_TX
#if ISRTYPE_USART2_TX != NONE
#if ISRTYPE_USART2_TX == BLOCK

ISR(USART2_TX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART2_TX)
		Interrupt::invoke<USART2_TX_vect_num>();
}

#elif ISRTYPE_USART2_TX == NOBLOCK

ISR(USART2_TX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART2_TX)
		Interrupt::invoke<USART2_TX_vect_num>();
}

#endif
#endif

//USART3_TX
#if ISRTYPE_USART3_TX != NONE
#if ISRTYPE_USART3_TX == BLOCK

ISR(USART3_TX_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART3_TX)
		Interrupt::invoke<USART3_TX_vect_num>();
}

#elif ISRTYPE_USART3_TX == NOBLOCK

ISR(USART3_TX_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART3_TX)
		Interrupt::invoke<USART3_TX_vect_num>();
}

#endif
#endif


//___________________________________
//Usart UDRE

//USART0_UDRE
#if ISRTYPE_USART0_UDRE != NONE
#if ISRTYPE_USART0_UDRE == BLOCK

ISR(USART0_UDRE_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART0_UDRE)
		Interrupt::invoke<USART0_UDRE_vect_num>();
}

#elif ISRTYPE_USART0_UDRE == NOBLOCK

ISR(USART0_UDRE_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART0_UDRE)
		Interrupt::invoke<USART0_UDRE_vect_num>();
}

#endif
#endif

//USART1_UDRE
#if ISRTYPE_USART1_UDRE != NONE
#if ISRTYPE_USART1_UDRE == BLOCK

ISR(USART1_UDRE_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART1_UDRE)
		Interrupt::invoke<USART1_UDRE_vect_num>();
}

#elif ISRTYPE_USART1_UDRE == NOBLOCK

ISR(USART1_UDRE_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART1_UDRE)
		Interrupt::invoke<USART1_UDRE_vect_num>();
}

#endif
#endif

//USART2_UDRE
#if ISRTYPE_USART2_UDRE != NONE
#if ISRTYPE_USART2_UDRE == BLOCK

ISR(USART2_UDRE_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART2_UDRE)
		Interrupt::invoke<USART2_UDRE_vect_num>();
}

#elif ISRTYPE_USART2_UDRE == NOBLOCK

ISR(USART2_UDRE_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART2_UDRE)
		Interrupt::invoke<USART2_UDRE_vect_num>();
}

#endif
#endif

//USART3_UDRE
#if ISRTYPE_USART3_UDRE != NONE
#if ISRTYPE_USART3_UDRE == BLOCK

ISR(USART3_UDRE_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_USART3_UDRE)
		Interrupt::invoke<USART3_UDRE_vect_num>();
}

#elif ISRTYPE_USART3_UDRE == NOBLOCK

ISR(USART3_UDRE_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_USART3_UDRE)
		Interrupt::invoke<USART3_UDRE_vect_num>();
}

#endif
#endif

//___________________________________
//Timer	OC

//TIMER0 OCA
#if ISRTYPE_TIMER0_OCA != NONE
#if ISRTYPE_TIMER0_OCA == BLOCK

ISR(TIMER0_COMPA_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_TIMER0_OC_A)
		Interrupt::invoke<TIMER0_COMPA_vect_num>();
}

#elif ISRTYPE_TIMER0_OCA == NOBLOCK

ISR(TIMER0_COMPA_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_TIMER0_OC_A)
		Interrupt::invoke<TIMER0_COMPA_vect_num>();
}

#endif
#endif

//TIMER0 OCB
#if ISRTYPE_TIMER0_OCB != NONE
#if ISRTYPE_TIMER0_OCB == BLOCK

ISR(TIMER0_COMPB_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_TIMER0_OC_B)
		Interrupt::invoke<TIMER0_COMPB_vect_num>();
}

#elif ISRTYPE_TIMER0_OCB == NOBLOCK

ISR(TIMER0_COMPB_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_TIMER0_OC_B)
		Interrupt::invoke<TIMER0_COMPB_vect_num>();
}

#endif
#endif

//TIMER2 OCA
#if ISRTYPE_TIMER2_OCA != NONE
#if ISRTYPE_TIMER2_OCA == BLOCK

ISR(TIMER2_COMPA_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_TIMER2_OC_A)
		Interrupt::invoke<TIMER2_COMPA_vect_num>();
}

#elif ISRTYPE_TIMER2_OCA == NOBLOCK

ISR(TIMER2_COMPA_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_TIMER2_OC_A)
		Interrupt::invoke<TIMER2_COMPA_vect_num>();
}

#endif
#endif

//TIMER2 OCB
#if ISRTYPE_TIMER2_OCB != NONE
#if ISRTYPE_TIMER2_OCB == BLOCK

ISR(TIMER2_COMPB_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_TIMER2_OC_B)
		Interrupt::invoke<TIMER2_COMPB_vect_num>();
}

#elif ISRTYPE_TIMER2_OCB == NOBLOCK

ISR(TIMER2_COMPB_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_TIMER2_OC_B)
		Interrupt::invoke<TIMER2_COMPB_vect_num>();
}

#endif
#endif

//___________________________________
//Timer	OVF

//TIMER0 OVF
#if ISRTYPE_TIMER0_OVF != NONE
#if ISRTYPE_TIMER0_OVF == BLOCK

ISR(TIMER0_OVF_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_TIMER0_OVF)
		Interrupt::invoke<TIMER0_OVF_vect_num>();
}

#elif ISRTYPE_TIMER0_OVF == NOBLOCK

ISR(TIMER0_OVF_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_TIMER0_OVF)
		Interrupt::invoke<TIMER0_OVF_vect_num>();
}

#endif
#endif

//TIMER2 OVF
#if ISRTYPE_TIMER2_OVF != NONE
#if ISRTYPE_TIMER2_OVF == BLOCK

ISR(TIMER2_OVF_vect, ISR_BLOCK) {
	if (Configuration::enableInterrupt_TIMER2_OVF)
		Interrupt::invoke<TIMER2_OVF_vect_num>();
}

#elif ISRTYPE_TIMER2_OVF == NOBLOCK

ISR(TIMER2_OVF_vect, ISR_NOBLOCK) {
	if (Configuration::enableInterrupt_TIMER2_OVF)
		Interrupt::invoke<TIMER2_OVF_vect_num>();
}

#endif
#endif
