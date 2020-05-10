#include <util/atomic.h>
#include "Interrupt.h"


#if INTERRUPTTYPE == UNIVERSAL

void Interrupt::registerCallback(Callback callback) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		this->target.callbackType = true;
		if (callback == nullptr) {
			this->target.pointer.callback = &DefaultHandler::nothing;
		}
		else {
			this->target.pointer.callback = callback;
		}
	}
}

void Interrupt::registerListener(InterruptListener& listener) noexcept {
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

#elif INTERRUPTTYPE == TRIGGER

void Interrupt::registerListener(InterruptListener& listener) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		this->target = &listener;
	}
}

#endif
