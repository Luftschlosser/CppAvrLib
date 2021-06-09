#include <avr/interrupt.h>
#include "../Configuration.h"
#include "../interrupts/Interrupt.h"

//Empty ISR-Routine: 82 Byte


//___________________________________
//External Interrupts

#if ISRTYPE_EXT_INT0 != NONE
#if ISRTYPE_EXT_INT0 == BLOCK

ISR(INT0_vect, ISR_BLOCK) {
	Interrupt::invoke<INT0_vect_num>();
}

#elif ISRTYPE_EXT_INT0 == NOBLOCK

ISR(INT0_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT0_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT1 != NONE
#if ISRTYPE_EXT_INT1 == BLOCK

ISR(INT1_vect, ISR_BLOCK) {
	Interrupt::invoke<INT1_vect_num>();
}

#elif ISRTYPE_EXT_INT1 == NOBLOCK

ISR(INT1_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT1_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT2 != NONE
#if ISRTYPE_EXT_INT2 == BLOCK

ISR(INT2_vect, ISR_BLOCK) {
	Interrupt::invoke<INT2_vect_num>();
}

#elif ISRTYPE_EXT_INT2 == NOBLOCK

ISR(INT2_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT2_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT3 != NONE
#if ISRTYPE_EXT_INT3 == BLOCK

ISR(INT3_vect, ISR_BLOCK) {
	Interrupt::invoke<INT3_vect_num>();
}

#elif ISRTYPE_EXT_INT3 == NOBLOCK

ISR(INT3_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT3_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT4 != NONE
#if ISRTYPE_EXT_INT4 == BLOCK

ISR(INT4_vect, ISR_BLOCK) {
	Interrupt::invoke<INT4_vect_num>();
}

#elif ISRTYPE_EXT_INT4 == NOBLOCK

ISR(INT4_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT4_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT5 != NONE
#if ISRTYPE_EXT_INT5 == BLOCK

ISR(INT5_vect, ISR_BLOCK) {
	Interrupt::invoke<INT5_vect_num>();
}

#elif ISRTYPE_EXT_INT5 == NOBLOCK

ISR(INT5_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT5_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT6 != NONE
#if ISRTYPE_EXT_INT6 == BLOCK

ISR(INT6_vect, ISR_BLOCK) {
	Interrupt::invoke<INT6_vect_num>();
}

#elif ISRTYPE_EXT_INT6 == NOBLOCK

ISR(INT6_vect, ISR_NOBLOCK) {
	Interrupt::invoke<INT6_vect_num>();
}

#endif
#endif

#if ISRTYPE_EXT_INT7 != NONE
#if ISRTYPE_EXT_INT7 == BLOCK

ISR(INT7_vect, ISR_BLOCK) {
	Interrupt::invoke<INT7_vect_num>();
}

#elif ISRTYPE_EXT_INT7 == NOBLOCK

ISR(INT7_vect, ISR_NOBLOCK) {
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
	Interrupt::invoke<USART0_RX_vect_num>();
}

#elif ISRTYPE_USART0_RX == NOBLOCK

ISR(USART0_RX_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART0_RX_vect_num>();
}

#endif
#endif

//USART1_RX
#if ISRTYPE_USART1_RX != NONE
#if ISRTYPE_USART1_RX == BLOCK

ISR(USART1_RX_vect, ISR_BLOCK) {
	Interrupt::invoke<USART1_RX_vect_num>();
}

#elif ISRTYPE_USART1_RX == NOBLOCK

ISR(USART1_RX_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART1_RX_vect_num>();
}

#endif
#endif

//USART2_RX
#if ISRTYPE_USART2_RX != NONE
#if ISRTYPE_USART2_RX == BLOCK

ISR(USART2_RX_vect, ISR_BLOCK) {
	Interrupt::invoke<USART2_RX_vect_num>();
}

#elif ISRTYPE_USART2_RX == NOBLOCK

ISR(USART2_RX_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART2_RX_vect_num>();
}

#endif
#endif

//USART3_RX
#if ISRTYPE_USART3_RX != NONE
#if ISRTYPE_USART3_RX == BLOCK

ISR(USART3_RX_vect, ISR_BLOCK) {
	Interrupt::invoke<USART3_RX_vect_num>();
}

#elif ISRTYPE_USART3_RX == NOBLOCK

ISR(USART3_RX_vect, ISR_NOBLOCK) {
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
	Interrupt::invoke<USART0_TX_vect_num>();
}

#elif ISRTYPE_USART0_TX == NOBLOCK

ISR(USART0_TX_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART0_TX_vect_num>();
}

#endif
#endif

//USART1_RX
#if ISRTYPE_USART1_TX != NONE
#if ISRTYPE_USART1_TX == BLOCK

ISR(USART1_TX_vect, ISR_BLOCK) {
	Interrupt::invoke<USART1_TX_vect_num>();
}

#elif ISRTYPE_USART1_TX == NOBLOCK

ISR(USART1_TX_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART1_TX_vect_num>();
}

#endif
#endif

//USART2_RX
#if ISRTYPE_USART2_TX != NONE
#if ISRTYPE_USART2_TX == BLOCK

ISR(USART2_TX_vect, ISR_BLOCK) {
	Interrupt::invoke<USART2_TX_vect_num>();
}

#elif ISRTYPE_USART2_TX == NOBLOCK

ISR(USART2_TX_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART2_TX_vect_num>();
}

#endif
#endif

//USART3_RX
#if ISRTYPE_USART3_TX != NONE
#if ISRTYPE_USART3_TX == BLOCK

ISR(USART3_TX_vect, ISR_BLOCK) {
	Interrupt::invoke<USART3_TX_vect_num>();
}

#elif ISRTYPE_USART3_TX == NOBLOCK

ISR(USART3_TX_vect, ISR_NOBLOCK) {
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
	Interrupt::invoke<USART0_UDRE_vect_num>();
}

#elif ISRTYPE_USART0_UDRE == NOBLOCK

ISR(USART0_UDRE_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART0_UDRE_vect_num>();
}

#endif
#endif

//USART1_RX
#if ISRTYPE_USART1_UDRE != NONE
#if ISRTYPE_USART1_UDRE == BLOCK

ISR(USART1_UDRE_vect, ISR_BLOCK) {
	Interrupt::invoke<USART1_UDRE_vect_num>();
}

#elif ISRTYPE_USART1_UDRE == NOBLOCK

ISR(USART1_UDRE_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART1_UDRE_vect_num>();
}

#endif
#endif

//USART2_RX
#if ISRTYPE_USART2_UDRE != NONE
#if ISRTYPE_USART2_UDRE == BLOCK

ISR(USART2_UDRE_vect, ISR_BLOCK) {
	Interrupt::invoke<USART2_UDRE_vect_num>();
}

#elif ISRTYPE_USART2_UDRE == NOBLOCK

ISR(USART2_UDRE_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART2_UDRE_vect_num>();
}

#endif
#endif

//USART3_RX
#if ISRTYPE_USART3_UDRE != NONE
#if ISRTYPE_USART3_UDRE == BLOCK

ISR(USART3_UDRE_vect, ISR_BLOCK) {
	Interrupt::invoke<USART3_UDRE_vect_num>();
}

#elif ISRTYPE_USART3_UDRE == NOBLOCK

ISR(USART3_UDRE_vect, ISR_NOBLOCK) {
	Interrupt::invoke<USART3_UDRE_vect_num>();
}

#endif
#endif
