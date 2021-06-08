#include "Periphery.h"
#include "../periphery/InterruptPin.h"

template <> InterruptPin& Periphery::getInstance<InterruptPin, 0>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 0, 0);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 1>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 1, 1);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 2>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 2, 2);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 3>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 3, 3);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 4>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 4, 4);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 5>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 5, 5);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 6>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 6, 6);
	return iPin;
}
template <> InterruptPin& Periphery::getInstance<InterruptPin, 7>() {
	static InterruptPin iPin = InterruptPin(getInstance<Port, 'B'>(), 7, 7);
	return iPin;
}
