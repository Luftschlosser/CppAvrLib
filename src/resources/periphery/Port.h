#ifndef SRC_RESOURCES_PERIPHERY_PORT_H_
#define SRC_RESOURCES_PERIPHERY_PORT_H_


#include <stdlib.h>
#include "../Periphery.h"
#include <util/atomic.h>

class Pin;


class Port final {
	friend Pin;
	friend Periphery;

private:
	volatile uint8_t pinReg; //PINn
	volatile uint8_t ddrReg; //DDRn
	volatile uint8_t portReg; //PORTn

	static uint8_t usage[Periphery::getCapacity<Port>()];

	inline Port() noexcept {}

	inline void initPins(uint8_t mask) {
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
	inline void closePins(uint8_t mask) noexcept {
		if (Periphery::runtimeAllocationsEnabled) { //TODO: if constexpr, but need newer compiler for C++17
				uint8_t index = Periphery::getIdentity(this);
				usage[index] &= ~mask;
			}
	}
	inline bool arePinsUsed(uint8_t mask) noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return (usage[index] & mask) != 0;
	}

public:
	inline void init() {
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

	inline void close() noexcept {
		if (Periphery::runtimeAllocationsEnabled) { //TODO: if constexpr, but need newer compiler for C++17
			uint8_t index = Periphery::getIdentity(this);
			usage[index] = 0;
		}
	}

	inline bool isUsed() noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return usage[index] != 0;
	}

	inline void setOutput() noexcept { ddrReg = 0xFF; }
	inline void writeOutput(uint8_t data) noexcept { portReg = data; }
	inline uint8_t readOutput() noexcept { return portReg; }
	inline void toggleOutput() noexcept { pinReg = 0xFF; }
	inline void toggleOutput(uint8_t toggleMask) noexcept { pinReg = toggleMask; }

	inline void setInput() noexcept { ddrReg = 0; }
	inline uint8_t readInput() noexcept { return pinReg; }
	inline void writeInputPullups(uint8_t mask) noexcept { portReg = mask; }
	inline uint8_t readInputPullups() noexcept { return portReg; }

	inline void writeDataDirections(uint8_t directionMask) noexcept { ddrReg = directionMask; }
	inline uint8_t readDataDirections() noexcept { return ddrReg; }
};


#endif /* SRC_RESOURCES_PERIPHERY_PORT_H_ */
