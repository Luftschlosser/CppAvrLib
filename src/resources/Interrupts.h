#ifndef SRC_RESOURCES_INTERRUPTS_H_
#define SRC_RESOURCES_INTERRUPTS_H_

#include "interrupts/Interrupt.h"

#if defined(__AVR_ATmega2560__)
	#include "./m2560/Interrupts.h"
#elif defined(__AVR_ATmega328P__)
	#include "./m328p/Interrupts.h"
#elif defined(__AVR_ATmega328PB__)
	#include "./m328pb/Interrupts.h"
#endif

#endif /* SRC_RESOURCES_INTERRUPTS_H_ */
