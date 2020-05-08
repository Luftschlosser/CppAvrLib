#include <avr/interrupt.h>
#include "InterruptUsart0Rx.h"


using namespace InterruptUsart0Rx;

#if ISRTYPE_USART0_RX == UNIVERSAL

InterruptSource::TargetPointer Manager::target = {&DefaultHandler::nothing};
bool Manager::callback = true;

void Manager::registerCallback(callback_t callback) noexcept {
	InterruptSource::registerCallback(callback, &Manager::target, &Manager::callback);
}

void Manager::registerListener(IrqListener* listener) noexcept {
	InterruptSource::registerListener(listener, &Manager::target, &Manager::callback);
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

InterruptSource::callback_t Manager::callback = &DefaultHandler::nothing;

void Manager::registerCallback(callback_t callback) noexcept {
	InterruptSource::registerCallback(callback, &Manager::callback);
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

void Manager::registerListener(IrqListener* listener) noexcept {
	InterruptSource::registerListener(listener, &Manager::listener);
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
