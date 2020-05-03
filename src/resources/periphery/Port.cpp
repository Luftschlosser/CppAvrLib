#include "Port.h"
#include <util/atomic.h>

uint8_t Port::usage[] = {};

void Port::init() {
		if (Periphery::runtimeAllocationsEnabled) { //TODO: if constexpr, but need newer compiler for C++17
			uint8_t index = Periphery::getIdentity(this);
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				if (usage[index] == 0) {
					usage[index] = 0xFF; //Set all Pins in use
				}
				else {
					//throw later (check possible problems with throwing in atomic block)
				}
			}
		}
	}

void Port::initPins(uint8_t mask) {
	if (Periphery::runtimeAllocationsEnabled) { //TODO: if constexpr, but need newer compiler for C++17
		uint8_t index = Periphery::getIdentity(this);
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if (usage[index] & mask) {
				//throw later (check possible problems with throwing in atomic block)
			}
			else {
				usage[index] |= mask;
			}
		}
	}
}

inline void Port::close() noexcept {
	if (Periphery::runtimeAllocationsEnabled) { //TODO: if constexpr, but need newer compiler for C++17
		uint8_t index = Periphery::getIdentity(this);
		usage[index] = 0;
	}
}

inline void Port::closePins(uint8_t mask) noexcept {
	if (Periphery::runtimeAllocationsEnabled) { //TODO: if constexpr, but need newer compiler for C++17
			uint8_t index = Periphery::getIdentity(this);
			usage[index] &= ~mask;
		}
}

inline bool Port::isUsed() noexcept {
	uint8_t index = Periphery::getIdentity(this);
	return usage[index] != 0;
}

inline bool Port::arePinsUsed(uint8_t mask) noexcept {
	uint8_t index = Periphery::getIdentity(this);
	return (usage[index] & mask) != 0;
}
