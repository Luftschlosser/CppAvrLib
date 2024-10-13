#ifndef SRC_RESOURCES_INTERRUPTS_H_
#define SRC_RESOURCES_INTERRUPTS_H_

#define __AVR_ATmega328PB__

#include "interrupts/Interrupt.h"

#if defined(__AVR_ATmega2560__)
	#include "./m2560/Interrupts.h"
#elif defined(__AVR_ATmega328P__)
	#if defined(__AVR_ATmega328PB__) //Botch to make it work without proper IDE Support -> Todo
		#include "./m328pb/Interrupts.h"
	#else
		#include "./m328p/Interrupts.h"
	#endif
#endif

#endif /* SRC_RESOURCES_INTERRUPTS_H_ */
