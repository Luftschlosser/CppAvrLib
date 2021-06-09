#ifndef SRC_RESOURCES_PERIPHERY_INTERRUPTPIN_H_
#define SRC_RESOURCES_PERIPHERY_INTERRUPTPIN_H_


#include "Pin.h"


//Forward-Declarations
namespace Periphery {
	template <typename T, unsigned char Index> inline T& getInstance();
}


//Wraps external PCINT interrupt
class InterruptPin final : public Pin {
	template <typename T, unsigned char Index> friend T& Periphery::getInstance(); //Allows Constructor-Access for Factory-Function

private:

	const uint8_t interruptNumber;

	static constexpr intptr_t regEIFR = ADR_EIFR;
	static constexpr intptr_t regEIMSK = ADR_EIMSK;
	static constexpr intptr_t regEICRA = ADR_EICRA;


	///Constructor (can produce const instances when used with const parameters)
	///\param port The Port this InterruptPin is part of
	///\param pin The Pin of the Port which is represented by this InterruptPin
	///\param interruptNumber The number of the associated external interrupt. [0-7]
	inline constexpr InterruptPin (Port& port, uint8_t pin, uint8_t interruptNumber) noexcept :
			Pin(port,pin), interruptNumber(interruptNumber) {}

public:

	enum InterruptSenseMode : uint8_t {
		LOW_LEVEL = 0,
		TOGGLE = 1,
		FALLING_EDGE = 2,
		RISING_EDGE = 3
	};

	inline void setInterruptMode(InterruptSenseMode mode) const noexcept {
		uint8_t shift = (interruptNumber * 2) % 8;
		uint8_t* target = reinterpret_cast<uint8_t*>(regEICRA + (interruptNumber / 4));
		*target = (*target & ~(3 << shift)) | (mode << shift);
	}

	inline void enableInterrupt() const noexcept { *reinterpret_cast<uint8_t*>(regEIMSK) |= (1 << interruptNumber); }

	inline void disableInterrupt() const noexcept { *reinterpret_cast<uint8_t*>(regEIMSK) &= ~(1 << interruptNumber); }

	inline void clearInterrupt() const noexcept { *reinterpret_cast<uint8_t*>(regEIFR) |= (1 << interruptNumber); }
};


#endif /* SRC_RESOURCES_PERIPHERY_INTERRUPTPIN_H_ */
