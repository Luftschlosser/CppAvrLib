#include <avr/interrupt.h>
#include "../Configuration.h"
#include "../interrupts/Interrupt.h"


//ISR-Routine (enabled)	: 98B ROM + 4B RAM
//ISR-Routine (empty)	: 20B ROM + 0B RAM


#if defined(__AVR_ATmega328P__)
//_____________________________________________
//INTERRUPT-CONFIGURATION:2

//Implementation Type configuration for each Interrupt source [ISR_NAKED / ISR_BLOCK / ISR_NOBLOCK] (Comment out #define to omit ISR-Routine completely)
#define ISRTYPE_EXT_INT0 	ISR_BLOCK
#define ISRTYPE_EXT_INT1 	ISR_BLOCK

#define ISRTYPE_PCINT0		ISR_BLOCK
#define ISRTYPE_PCINT1		ISR_BLOCK
#define ISRTYPE_PCINT2		ISR_BLOCK

#define ISRTYPE_USART_RX 	ISR_BLOCK
#define ISRTYPE_USART_TX 	ISR_BLOCK
#define ISRTYPE_USART_UDRE	ISR_BLOCK

#define ISRTYPE_TIMER0_OCA	ISR_BLOCK
#define ISRTYPE_TIMER0_OCB	ISR_BLOCK
#define ISRTYPE_TIMER0_OVF	ISR_BLOCK
#define ISRTYPE_TIMER1_OCA	ISR_BLOCK
#define ISRTYPE_TIMER1_OCB	ISR_BLOCK
#define ISRTYPE_TIMER1_OVF	ISR_BLOCK
#define ISRTYPE_TIMER1_CAPT	ISR_BLOCK
#define ISRTYPE_TIMER2_OCA	ISR_BLOCK
#define ISRTYPE_TIMER2_OCB	ISR_BLOCK
#define ISRTYPE_TIMER2_OVF	ISR_BLOCK

#define ISRTYPE_TWI			ISR_BLOCK
#define ISRTYPE_ADC			ISR_BLOCK
#define ISRTYPE_WDT			ISR_BLOCK
#define ISRTYPE_EEPROM		ISR_BLOCK

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
#ifdef ISRTYPE_USART_RX
ISR(USART_RX_vect , ISRTYPE_USART_RX) {
	if (Configuration::enableInterrupt_USART0_RX)
		Interrupt::invoke<USART_RX_vect_num>();
}
#endif

//___________________________________
//Usart TX

//USART0_TX
#ifdef ISRTYPE_USART_TX
ISR(USART_TX_vect, ISRTYPE_USART_TX) {
	if (Configuration::enableInterrupt_USART0_TX)
		Interrupt::invoke<USART_TX_vect_num>();
}
#endif

//___________________________________
//Usart UDRE

//USART0_UDRE
#ifdef ISRTYPE_USART_UDRE
ISR(USART_UDRE_vect, ISRTYPE_USART_UDRE) {
	if (Configuration::enableInterrupt_USART0_UDRE)
		Interrupt::invoke<USART_UDRE_vect_num>();
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

//___________________________________
//Timer	CAPT

//TIMER1 CAPT
#ifdef ISRTYPE_TIMER1_CAPT
ISR(TIMER1_CAPT_vect, ISRTYPE_TIMER1_CAPT) {
	if (Configuration::enableInterrupt_TIMER1_CAPT)
		Interrupt::invoke<TIMER1_CAPT_vect_num>();
}
#endif

//___________________________________
//TWI

//TWI
#ifdef ISRTYPE_TWI
ISR(TWI_vect, ISRTYPE_TWI) {
	if (Configuration::enableInterrupt_TWI)
		Interrupt::invoke<TWI_vect_num>();
}
#endif

//___________________________________
//ADC

//ADC
#ifdef ISRTYPE_ADC
ISR(ADC_vect, ISRTYPE_ADC) {
	if (Configuration::enableInterrupt_ADC)
		Interrupt::invoke<ADC_vect_num>();
}
#endif

//___________________________________
//WDT

//ADC
#ifdef ISRTYPE_WDT
ISR(WDT_vect, ISRTYPE_WDT) {
	if (Configuration::enableInterrupt_WDT)
		Interrupt::invoke<WDT_vect_num>();
}
#endif

//___________________________________
//EEPROM READY

//ADC
#ifdef ISRTYPE_EEPROM
ISR(EE_READY_vect, ISRTYPE_EEPROM) {
	if (Configuration::enableInterrupt_EEPROM)
		Interrupt::invoke<EE_READY_vect_num>();
}
#endif


#endif
