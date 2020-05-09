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
		this->target.pointer.listener = listener;
	}
}

#elif INTERRUPTTYPE == CALLBACK

EventSource::Callback Interrupt::targets[] = {&DefaultHandler::nothing};

void Interrupt::registerCallback(Callback callback) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (callback == nullptr) {
			Interrupt::targets[this->vectorNumber] = &DefaultHandler::nothing;
		}
		else {
			Interrupt::targets[this->vectorNumber] = callback;
		}
	}
}

void Interrupt::registerListener(Listener& listener) {
	//TODO: throw
}

#elif INTERRUPTTYPE == TRIGGER

Listener* Interrupt::targets[] = { &DefaultHandler::NoListener::getInstance() };

void Interrupt::registerCallback(Callback callback) {
	//TODO: throw
}

void Interrupt::registerListener(Listener& listener) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		Interrupt::targets[this->vectorNumber] = &listener;
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
