#ifndef SRC_RESOURCES_INTERRUPTS_LISTENER_H_
#define SRC_RESOURCES_INTERRUPTS_LISTENER_H_


#include "../../cpp/VirtualMembers.h"


class Listener {

protected:

	~Listener() noexcept {}

public:

	virtual void trigger() noexcept = 0;
};


#endif /* SRC_RESOURCES_INTERRUPTS_LISTENER_H_ */
