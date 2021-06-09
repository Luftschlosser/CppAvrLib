#ifndef SRC_RESOURCES_PERIPHERY_GENERALPURPOSEFLAG_H_
#define SRC_RESOURCES_PERIPHERY_GENERALPURPOSEFLAG_H_


#include <stdint.h>
#include "../GeneralPurposeRegister.h"
#include "../../Configuration.h"
#include "../utilities/RuntimeAllocator.h"

///Abstraction of one Bit of a GeneralPurposeRegister. Can be accessed really fast when using a const Instance.
class GeneralPurposeFlag final {
	friend bool RuntimeAllocator::allocate(const GeneralPurposeFlag* object); //Allows Allocator access to GeneralPurposeRegister
	friend void RuntimeAllocator::deallocate(const GeneralPurposeFlag* object); //Allows Deallocator access to GeneralPurposeRegister
	friend bool RuntimeAllocator::isAllocated(const GeneralPurposeFlag* object); //Allows isAllocated access to GeneralPurposeRegister

private:

	///The GeneralPurposeRegister this GeneralPurposeFlag is part of
	GeneralPurposeRegister& gpior;

	///The Bit of the GeneralPurposeRegister which is represented by this GeneralPurposeFlag
	const uint8_t bit;

public:

	///Constructor (can produce const instances when used with const parameters)
	///\param gpioRegister The GeneralPurposeRegister this GeneralPurposeFlag is part of
	///\param bit The Bit of the GeneralPurposeRegister which is represented by this GeneralPurposeFlag
	inline constexpr GeneralPurposeFlag (GeneralPurposeRegister& gpioRegister, uint8_t bit) noexcept : gpior(gpioRegister), bit(bit) {}

	///Returns the Bit number of this bit within the GeneralPuposeRegister
	///\returns [0-7]
	inline uint8_t getBitNumber() const noexcept { return bit; }

	///Initializes the GeneralPurposeFlag
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the GeneralPurposeFlag
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the GeneralPurposeFlag
	///\return true if the GeneralPurposeFlag is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	///Writes a given Bit to the Flag
	///\param data the boolean value to write
	inline void write(bool data) const noexcept { if (data) gpior.regGPIOR |= (1 << bit); else gpior.regGPIOR &= ~(1 << bit); }

	///Sets the Flag to High
	inline void setHigh() const noexcept { gpior.regGPIOR |= (1 << bit); }

	///Sets the Flag to Low
	inline void setLow() const noexcept { gpior.regGPIOR &= ~(1 << bit); }

	///Read the Flag value
	///\return the boolean value which is currently hold be the GeneralPurposeFlag
	inline bool read() const noexcept { return gpior.regGPIOR & (1 << bit); }
};


#endif /* SRC_RESOURCES_PERIPHERY_GENERALPURPOSEFLAG_H_ */
