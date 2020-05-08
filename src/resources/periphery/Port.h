#ifndef SRC_RESOURCES_PERIPHERY_PORT_H_
#define SRC_RESOURCES_PERIPHERY_PORT_H_


#include <stdint.h>
#include "../Periphery.h"
#include <util/atomic.h>


//Forward-Declarations
class Pin;


///MMIO Abstraction of the GPIO Ports
class Port final {
	friend Pin;

private:

	///Allocation Flags for all Ports (and Pins) TODO: Inhibit when Periphery::runtimeAllocationsEnabled==false
	static uint8_t usage[Periphery::getCapacity<Port>()];

	///No Constructor to prohibit instantiation
	Port() = delete;

	///Allows initialization of a subset of Pins (used by friend-classes)
	///\param mask the bitmask to select the pins to initialize
	inline void initPins(uint8_t mask) {
	if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				if (usage[index] & mask) {
					//Todo: throw later (check possible problems with throwing in atomic block)
				}
				else {
					usage[index] |= mask;
				}
			}
		}
	}

	///Allows de-initialization of a subset of Pins (used by friend-classes)
	///\param mask the bitmask to select the pins to de-initialize
	inline void closePins(uint8_t mask) noexcept {
		if (Periphery::runtimeAllocationsEnabled) {
				uint8_t index = Periphery::getIdentity(this);
				usage[index] &= ~mask;
			}
	}

	///Allows checking the usage of a subset of Pins (used by friend-classes)
	///\param mask the bitmask to select the pins to check
	///\return true if the selected Pins are already in use, else false
	inline bool arePinsUsed(uint8_t mask) noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return (usage[index] & mask) != 0;
	}


public:

	///The PINn register
	volatile uint8_t regPIN;

	///The DDRn register
	volatile uint8_t regDDR;

	///The PORTn register
	volatile uint8_t regPORT;

	///Enumeration to describe the mode of operation
	enum Mode : uint8_t {
		OUTPUT,
		INPUT,
		INPUT_PULLUP
	};

	///Initializes the entire Port
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

	///De-Initializes the entire Port
	inline void close() noexcept {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			usage[index] = 0;
		}
	}

	///checks the usage of the Port
	///\return true if at least one Pin of the Port is already in use, else false
	inline bool isUsed() noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return usage[index] != 0;
	}

	///Sets the mode of operation for the entire Port
	///\param mode the mode of operation to configure
	inline void setMode(Mode mode) noexcept {
		switch (mode) {
		case Mode::OUTPUT:
			regDDR = 0xFF;
			break;
		case Mode::INPUT:
			regDDR = 0x00;
			regPORT = 0x00;
			break;
		case Mode::INPUT_PULLUP:
			regDDR = 0x00;
			regPORT = 0xFF;
			break;
		}
	}

	///Writes data to the Port (in Output mode)
	///\param data the byte to write to the port
	inline void write(uint8_t data) noexcept { regPORT = data; }

	///Toggles all Bits of the Port (in Output mode)
	inline void toggle() noexcept { regPIN = 0xFF; }

	///Reads data from the Port (in Input mode)
	///return the byte which is currently on the port
	inline uint8_t read() noexcept { return regPIN; }
};


#endif /* SRC_RESOURCES_PERIPHERY_PORT_H_ */
