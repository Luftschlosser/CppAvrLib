#include <avr/interrupt.h>
#include "../interrupts/InterruptConfiguration.h"
#include "../interrupts/Interrupt.h"

//Program memory consumption per ISR: [Implementation]
	//[UNIVERSAL]:	118 Byte
	//[CALLBACK]:	 86 Byte
	//[TRIGGER]:	102 Byte
	//Empty ISR-Routine: 82 Byte


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
