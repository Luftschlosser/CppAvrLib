#ifndef SRC_RESOURCES_PERIPHERY_GENERALPURPOSEREGISTER_H_
#define SRC_RESOURCES_PERIPHERY_GENERALPURPOSEREGISTER_H_


#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


//Forward-Declarations
class GeneralPurposeFlag;


///MMIO Abstraction of the General Purpose IO Registers. Can be accessed really fast (faster than a Byte in memory).
class GeneralPurposeRegister final {
	friend GeneralPurposeFlag;

private:

	///No Constructor to prohibit instantiation
	GeneralPurposeRegister() = delete;

public:

	///The GPIORn register
	volatile uint8_t regGPIOR;

	///Initializes the GeneralPurposeRegister
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the GeneralPurposeRegister
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the GeneralPurposeRegister
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	///Writes data to the GeneralPurposeRegister
	///\param data the byte to write to the GeneralPurposeRegister
	inline void write(uint8_t data) noexcept { regGPIOR = data;	}

	///Reads data from the GeneralPurposeRegister
	///return the byte which is currently on the GeneralPurposeRegister
	inline uint8_t read() const noexcept { return regGPIOR; }

	inline void setBit(uint8_t bit) noexcept { regGPIOR |= 1 << bit; }
	inline void clearBit(uint8_t bit) noexcept { regGPIOR &= ~(1<<bit); }
	inline bool isBitSet(uint8_t bit) noexcept { return regGPIOR & 1 << bit; }
};


#endif /* SRC_RESOURCES_PERIPHERY_GENERALPURPOSEREGISTER_H_ */
