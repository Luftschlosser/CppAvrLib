#ifndef SRC_RESOURCES_INTERRUPTS_EVENTSOURCE_H_
#define SRC_RESOURCES_INTERRUPTS_EVENTSOURCE_H_


#include "../../cpp/VirtualMembers.h"


class Listener;


class EventSource {

protected:

	//Type declaration for callback
	typedef void(*Callback)(void);

	//Type declaration for universal target pointer
	typedef union {
		Callback callback;
		Listener& listener;
	} TargetPointer;

	inline ~EventSource() noexcept {}

public:

	virtual void registerCallback(Callback callback) = 0;
	virtual void registerListener(Listener& listener) = 0;
};


#endif /* SRC_RESOURCES_INTERRUPTS_EVENTSOURCE_H_ */
