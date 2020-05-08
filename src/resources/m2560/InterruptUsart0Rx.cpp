#include <avr/interrupt.h>
#include <util/atomic.h>
#include "InterruptUsart0Rx.h"
#include "../interrupts/DefaultHandler.h"


using namespace InterruptUsart0Rx;

#if ISRTYPE_USART0_RX == UNIVERSAL

TargetPointer Manager::target = {&DefaultHandler::nothing};
bool Manager::callback = true;

void Manager::registerCallback(void (*callback)()) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		Manager::callback = true;
		if (callback == nullptr) {
			Manager::target.callback = &DefaultHandler::nothing;
			//TODO: throw
		}
		else {
			Manager::target.callback = callback;
		}
	}
}

void Manager::registerListener(IrqListener* listener) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (listener == nullptr) {
			Manager::callback = true;
			Manager::target.callback = &DefaultHandler::nothing;
			//TODO: throw
		}
		else {
			Manager::callback = false;
			Manager::target.listener = listener;
		}
	}
}

ISR(USART0_RX_vect) {
	if (Manager::callback) {
		Manager::target.callback();
	}
	else {
		Manager::target.listener->trigger();
	}
}

#elif ISRTYPE_USART0_RX == CALLBACK

void (*Manager::callback)() = &DefaultHandler::nothing;

void Manager::registerCallback(void (*callback)()) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (callback == nullptr) {
			Manager::callback = &DefaultHandler::nothing;
			//TODO: throw
		}
		else {
			Manager::callback = callback;
		}
	}
}

void Manager::registerListener(IrqListener* listener) {
	//TODO: throw
}

ISR(USART0_RX_vect) {
	Manager::callback();
}

#elif ISRTYPE_USART0_RX == TRIGGER

IrqListener* Manager::listener = DefaultHandler::NoListener::getInstance();

void Manager::registerCallback(void (*callback)()) {
	//TODO: throw
}

void Manager::registerListener(IrqListener* listener) {
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if (listener == nullptr) {
			Manager::listener = DefaultHandler::NoListener::getInstance();
			//TODO: throw
		}
		else {
			Manager::listener = listener;
		}
	}
}

ISR(USART0_RX_vect) {
	Manager::listener->trigger();
}

#else

void Manager::registerCallback(void (*callback)()) {
	//TODO: throw
}

void Manager::registerListener(IrqListener* listener) {
	//TODO: throw
}

#endif
