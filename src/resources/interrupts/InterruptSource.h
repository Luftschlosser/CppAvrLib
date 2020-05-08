#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPTSOURCE_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPTSOURCE_H_


#include "../../cpp/VirtualMembers.h"


class IrqListener;


class InterruptSource {

protected:

	//Type declaration for callback
	typedef void(*callback_t)(void);

	//Type declaration for universal target pointer
	typedef union {
		callback_t callback;
		IrqListener* listener;
	} TargetPointer;

	~InterruptSource() noexcept {}

	static void registerCallback(callback_t callback, callback_t* target) noexcept;
	static void registerCallback(callback_t callback, TargetPointer* target, bool* targetFlag) noexcept;
	static void registerListener(IrqListener* listener, IrqListener** target) noexcept;
	static void registerListener(IrqListener* listener, TargetPointer* target, bool* targetFlag) noexcept;

public:

	virtual void registerCallback(void (*callback)()) = 0;
	virtual void registerListener(IrqListener* listener) = 0;
};


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPTSOURCE_H_ */
