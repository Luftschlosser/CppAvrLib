#ifndef SRC_RESOURCES_PERIPHERY_PIN_H_
#define SRC_RESOURCES_PERIPHERY_PIN_H_


#include <stdint.h>
#include "Port.h"

///Abstraction of one Pin of a Port
class Pin {

private:

	///The Port this Pin is part of
	Port& port;

	///The Pin of the Port which is represented by this Pin
	const uint8_t pin;

public:

	///Enumeration declaration to describe the mode of operation
	enum Mode : uint8_t {
		OUTPUT,
		INPUT,
		INPUT_PULLUP
	};

	///Constructor (can produce const instances when used with const parameters)
	///\param port The Port this Pin is part of
	///\param pin The Pin of the Port which is represented by this Pin
	inline constexpr Pin (Port& port, uint8_t pin) noexcept : port(port), pin(pin) {}

	///Initializes the Pin
	inline void init() const { port.initPins(1 << pin); }

	///De-Initializes the Pin
	inline void close() const noexcept { port.closePins(1 << pin); }

	///checks the usage of the Pin
	///\return true if the Pin is already in use, else false
	inline bool isUsed() const noexcept { return port.arePinsUsed(1 << pin); }

	///Sets the mode of operation for the Pin
	///\param mode the mode of operation to configure
	inline void setMode(const Mode mode) const noexcept {
		switch(mode) {
		case Mode::OUTPUT:
			port.regDDR |= (1 << pin);
			break;
		case Mode::INPUT:
			port.regDDR &= ~(1 << pin);
			port.regPORT &= ~(1 << pin);
			break;
		case Mode::INPUT_PULLUP:
			port.regDDR &= ~(1 << pin);
			port.regPORT |= (1 << pin);
			break;
		}
	}

	///Writes a given Bit to the Pin (in Output mode)
	///\param data the boolean value to output
	inline void write(bool data) const noexcept { if (data) port.regPORT |= (1 << pin); else port.regPORT &= ~(1 << pin); }

	///Sets the Pin output to High (in Output mode)
	inline void setHigh() const noexcept { port.regPORT |= (1 << pin); }

	///Sets the Pin output to Low (in Output mode)
	inline void setLow() const noexcept { port.regPORT &= ~(1 << pin); }

	///Toggles the Pin output (in Output mode)
	inline void toggle() const noexcept { port.regPIN |= (1 << pin); }

	///Read the Pin value (in Input mode)
	///\return the boolean value which is currently on the Pin
	inline bool read() const noexcept { return port.regPIN & (1 << pin); }
};


#endif /* SRC_RESOURCES_PERIPHERY_PIN_H_ */
