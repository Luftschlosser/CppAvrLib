#include "InterruptSource.h"
#include <util/atomic.h>
#include "DefaultHandler.h"

void InterruptSource::registerCallback(callback_t callback, callback_t* target) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (callback == nullptr) {
			*target = &DefaultHandler::nothing;
		}
		else {
			*target = callback;
		}
	}
}

void InterruptSource::registerCallback(callback_t callback, TargetPointer* target, bool* targetFlag) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		*targetFlag = true;
		if (callback == nullptr) {
			target->callback = &DefaultHandler::nothing;
		}
		else {
			target->callback = callback;
		}
	}
}

void InterruptSource::registerListener(IrqListener* listener, IrqListener** target) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (listener == nullptr) {
			*target = DefaultHandler::NoListener::getInstance();
		}
		else {
			*target = listener;
		}
	}
}

void InterruptSource::registerListener(IrqListener* listener, TargetPointer* target, bool* targetFlag) noexcept {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (listener == nullptr) {
			*targetFlag = true;
			target->callback = &DefaultHandler::nothing;
		}
		else {
			*targetFlag = false;
			target->listener = listener;
		}
	}
}
