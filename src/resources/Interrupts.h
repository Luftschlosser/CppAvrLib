#ifndef SRC_RESOURCES_INTERRUPTS_H_
#define SRC_RESOURCES_INTERRUPTS_H_

#include "./interrupts/InterruptSource.h"

#if defined(__AVR_ATmega2560__)
	#include "./m2560/InterruptUsart0Rx.h"
#endif

#endif /* SRC_RESOURCES_INTERRUPTS_H_ */
