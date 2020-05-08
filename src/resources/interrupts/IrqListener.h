#ifndef SRC_RESOURCES_INTERRUPTS_IRQLISTENER_H_
#define SRC_RESOURCES_INTERRUPTS_IRQLISTENER_H_


#include "../../cpp/VirtualMembers.h"


class IrqListener {

protected:

	~IrqListener() noexcept {}

public:

	virtual void trigger() noexcept = 0;
};


#endif /* SRC_RESOURCES_INTERRUPTS_IRQLISTENER_H_ */
