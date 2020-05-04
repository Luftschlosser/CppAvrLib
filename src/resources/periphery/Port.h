#ifndef SRC_RESOURCES_PERIPHERY_PORT_H_
#define SRC_RESOURCES_PERIPHERY_PORT_H_


#include <stdlib.h>
#include "../Periphery.h"
#include <util/atomic.h>


class Pin;


class Port final {
	friend Pin;

private:

	static uint8_t usage[Periphery::getCapacity<Port>()];

	Port() = delete; //Prohibit instantiation

	inline void initPins(uint8_t mask) {
	if (Periphery::runtimeAllocationsEnabled) {
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
		if (Periphery::runtimeAllocationsEnabled) {
				uint8_t index = Periphery::getIdentity(this);
				usage[index] &= ~mask;
			}
	}

	inline bool arePinsUsed(uint8_t mask) noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return (usage[index] & mask) != 0;
	}


public:

	volatile uint8_t regPIN;
	volatile uint8_t regDDR;
	volatile uint8_t regPORT;

	inline void init() {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				if (usage[index] == 0) {
					usage[index] = 0xFF; //Set all Pins in use
				}
				else {
					//Todo: throw later (check possible problems with throwing in atomic block)
				}
			}
		}
	}

	inline void close() noexcept {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			usage[index] = 0;
		}
	}

	inline bool isUsed() noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return usage[index] != 0;
	}

	inline void setOutput() noexcept { regDDR = 0xFF; }
	inline void writeOutput(uint8_t data) noexcept { regPORT = data; }
	inline uint8_t readOutput() noexcept { return regPORT; }
	inline void toggleOutput() noexcept { regPIN = 0xFF; }
	inline void toggleOutput(uint8_t toggleMask) noexcept { regPIN = toggleMask; }

	inline void setInput() noexcept { regDDR = 0; }
	inline uint8_t readInput() noexcept { return regPIN; }
	inline void writeInputPullups(uint8_t mask) noexcept { regPORT = mask; }
	inline uint8_t readInputPullups() noexcept { return regPORT; }

	inline void writeDataDirections(uint8_t directionMask) noexcept { regDDR = directionMask; }
	inline uint8_t readDataDirections() noexcept { return regDDR; }
};


#endif /* SRC_RESOURCES_PERIPHERY_PORT_H_ */
