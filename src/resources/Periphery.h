#ifndef SRC_RESOURCES_PERIPHERY_H_
#define SRC_RESOURCES_PERIPHERY_H_

#define __AVR_ATmega328PB__

#if defined(__AVR_ATmega2560__)
	#include "./m2560/Periphery.h"
#elif defined(__AVR_ATmega328P__)
	#if defined(__AVR_ATmega328PB__) //Botch to make it work without proper IDE Support -> Todo
		#include "./m328pb/Periphery.h"
	#else
		#include "./m328p/Periphery.h"
	#endif
#endif

#endif /* SRC_RESOURCES_PERIPHERY_H_ */
