#ifndef SRC_RESOURCES_PERIPHERY_SECONDARY_PINCHANGEINTERRUPT_H_
#define SRC_RESOURCES_PERIPHERY_SECONDARY_PINCHANGEINTERRUPT_H_

#include <stdint.h>
#include "../../Configuration.h"
#include "../utilities/RuntimeAllocator.h"
#include "../Port.h"
#include "Pin.h"


/* IMPORTANT INFO!
 * A PinChangeInterruptPort does not always correspond to one specific Port!
 * (for example on the AtMega2560, PCINT8 is on Port E and PCINT9-PCINT15 on Port J)
 * Thus, this class mostly operates on individual Pins.
 * It also does not perform AuoPinAllocation or AutpPinConfiguration.
 */


//Forward-Declarations
class PinChangeInterrupt;
namespace Periphery {
	template <uint8_t Index> inline PinChangeInterrupt getPinChangeInterrupt() noexcept;
	inline Pin getPinChangeInterruptPin(uint8_t pinCangeInterruptIndex, uint8_t pinNumber) noexcept;
}

//Wraps external PinChange-Interrupt PCINTn
class PinChangeInterrupt final {
	template <uint8_t Index> friend inline PinChangeInterrupt Periphery::getPinChangeInterrupt(); //Allows Constructor-Access for Factory-Function
	friend bool RuntimeAllocator::allocate(const PinChangeInterrupt* object); //Allows Allocator access to pinCangeInterruptNumber
	friend void RuntimeAllocator::deallocate(const PinChangeInterrupt* object); //Allows Deallocator access to pinCangeInterruptNumber
	friend bool RuntimeAllocator::isAllocated(const PinChangeInterrupt* object); //Allows isAllocated access to pinCangeInterruptNumber

private:
	const uint8_t pinCangeInterruptIndex;

	static constexpr intptr_t regPCICR = ADR_PCICR;
	static constexpr intptr_t regPCIFR = ADR_PCIFR;


	///Constructor (can produce const instances when used with const parameters)
	///\param pcIntNumber The number of the associated PCINT Port. [0-2]
	inline constexpr PinChangeInterrupt (uint8_t pinCangeInterruptIndex) noexcept :
		pinCangeInterruptIndex(pinCangeInterruptIndex) {}

public:

	///Initializes the PinChangeInterrupt
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the PinChangeInterrupt
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the PinChangeInterrupt
	///\return true if the Pin is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	inline void setPinMask(uint8_t mask) const noexcept { *reinterpret_cast<uint8_t*>(AddressMap::getRegisterPCMSK(this->pinCangeInterruptIndex)) = mask; }
	inline uint8_t getPinMask() const noexcept { return *reinterpret_cast<uint8_t*>(AddressMap::getRegisterPCMSK(this->pinCangeInterruptIndex)); }

	inline void enablePin(uint8_t pinNumber) const noexcept {*reinterpret_cast<uint8_t*>(AddressMap::getRegisterPCMSK(this->pinCangeInterruptIndex)) |= (1 << pinNumber); }
	inline void disablePin(uint8_t pinNumber) const noexcept {*reinterpret_cast<uint8_t*>(AddressMap::getRegisterPCMSK(this->pinCangeInterruptIndex)) &= ~(1 << pinNumber); }

	inline Pin getPin(uint8_t pinNumber) const noexcept { return Periphery::getPinChangeInterruptPin(this->pinCangeInterruptIndex, pinNumber); }

	inline void enableInterrupt() const noexcept { *reinterpret_cast<uint8_t*>(regPCICR) |= (1 << pinCangeInterruptIndex); }
	inline void disableInterrupt() const noexcept { *reinterpret_cast<uint8_t*>(regPCICR) &= ~(1 << pinCangeInterruptIndex); }
	inline void clearInterrupt() const noexcept { *reinterpret_cast<uint8_t*>(regPCIFR) |= (1 << pinCangeInterruptIndex); }
};

#endif /* SRC_RESOURCES_PERIPHERY_SECONDARY_PINCHANGEINTERRUPT_H_ */
