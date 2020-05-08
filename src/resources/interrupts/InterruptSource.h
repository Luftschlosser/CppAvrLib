#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPTSOURCE_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPTSOURCE_H_


#include "../../cpp/VirtualMembers.h"


class IrqListener;


class InterruptSource {

protected:

	~InterruptSource() noexcept {}

public:

	virtual void registerCallback(void (*callback)()) = 0;
	virtual void registerListener(IrqListener* listener) = 0;
};


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPTSOURCE_H_ */
