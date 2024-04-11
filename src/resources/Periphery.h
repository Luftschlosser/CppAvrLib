#ifndef SRC_RESOURCES_PERIPHERY_H_
#define SRC_RESOURCES_PERIPHERY_H_

#if defined(__AVR_ATmega2560__)
	#include "./m2560/Periphery.h"
#elif defined(__AVR_ATmega328P__)
	#include "./m328p/Periphery.h"
#endif

#endif /* SRC_RESOURCES_PERIPHERY_H_ */
