#include <util/atomic.h>
#include "Interrupt.h"
#include "DefaultHandler.h"


#if INTERRUPTTYPE == UNIVERSAL

void Interrupt::registerCallback(Callback callback) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		this->target.callbackType = true;
		if (callback == nullptr) { //Todo: check if actually possible
			this->target.pointer.callback = &DefaultHandler::nothing;
		}
		else {
			this->target.pointer.callback = callback;
		}
	}
}

void Interrupt::registerListener(Listener& listener) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		this->target.callbackType = false;
		this->target.pointer.listener = &listener;
	}
}

#elif INTERRUPTTYPE == CALLBACK

void Interrupt::registerCallback(Callback callback) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (callback == nullptr) {
			this->target = &DefaultHandler::nothing;
		}
		else {
			this->target = callback;
		}
	}
}

void Interrupt::registerListener(Listener& listener) {
	//TODO: throw
}

#elif INTERRUPTTYPE == TRIGGER

void Interrupt::registerCallback(Callback callback) {
	//TODO: throw
}

void Interrupt::registerListener(Listener& listener) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		this->target = &listener;
	}
}

#else

void Interrupt::registerCallback(Callback callback) {
	//TODO: throw
}

void Interrupt::registerListener(Listener& listener) {
	//TODO: throw
}

#endif
