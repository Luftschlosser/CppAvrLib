#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPTLISTENER_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPTLISTENER_H_


#include "../../cpp/VirtualMembers.h"


class InterruptListener {

protected:

	~InterruptListener() noexcept {}

public:

	virtual void trigger() noexcept = 0;
};


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPTLISTENER_H_ */
