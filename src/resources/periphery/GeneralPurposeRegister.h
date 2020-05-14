#ifndef SRC_RESOURCES_PERIPHERY_GENERALPURPOSEREGISTER_H_
#define SRC_RESOURCES_PERIPHERY_GENERALPURPOSEREGISTER_H_


#include <stdint.h>
#include <util/atomic.h>
#include "../Periphery.h"


//Forward-Declarations
class GeneralPurposeFlag;


///MMIO Abstraction of the General Purpose IO Registers
class GeneralPurposeRegister final {
	friend GeneralPurposeFlag;

private:

	///Allocation Flags for all General Purpose IO Registers (And single Bits) TODO: Inhibit when Periphery::runtimeAllocationsEnabled==false
	static uint8_t usage[Periphery::getCapacity<GeneralPurposeRegister>()];

	///No Constructor to prohibit instantiation
	GeneralPurposeRegister() = delete;

	///Allows initialization of a subset of Bits (used by friend-classes)
	///\param mask the bitmask to select the Bits to initialize
	inline void initBits(uint8_t mask) {
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

	///Allows de-initialization of a subset of Bits (used by friend-classes)
	///\param mask the bitmask to select the Bitss to de-initialize
	inline void closeBits(uint8_t mask) noexcept {
		if (Periphery::runtimeAllocationsEnabled) {
				uint8_t index = Periphery::getIdentity(this);
				usage[index] &= ~mask;
			}
	}

	///Allows checking the usage of a subset of Bits (used by friend-classes)
	///\param mask the bitmask to select the Bits to check
	///\return true if the selected Bits are already in use, else false
	inline bool areBitsUsed(uint8_t mask) noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return (usage[index] & mask) != 0;
	}

public:

	///The GPIORn register
	volatile uint8_t regGPIOR;

	///Initializes the GeneralPurposeRegister
	inline void init() {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				if (usage[index]) {
					usage[index] = 0xFF;
				}
				else {
					//Todo: throw later (check possible problems with throwing in atomic block)
				}
			}
		}
	}

	///De-Initializes the GeneralPurposeRegister
	inline void close() noexcept {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			usage[index] = 0;
		}
	}

	///checks the usage of the GeneralPurposeRegister
	///\return true if it is already in use, else false
	inline bool isUsed() noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return usage[index] != 0;
	}

	///Writes data to the GeneralPurposeRegister
	///\param data the byte to write to the GeneralPurposeRegister
	inline void write(uint8_t data) noexcept { regGPIOR = data;	}

	///Reads data from the GeneralPurposeRegister
	///return the byte which is currently on the GeneralPurposeRegister
	inline uint8_t read() noexcept { return regGPIOR; }
};


#endif /* SRC_RESOURCES_PERIPHERY_GENERALPURPOSEREGISTER_H_ */
