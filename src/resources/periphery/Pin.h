#ifndef SRC_RESOURCES_PERIPHERY_PIN_H_
#define SRC_RESOURCES_PERIPHERY_PIN_H_


#include <stdint.h>
#include "Port.h"


class Pin {

private:
	Port& port;
	const uint8_t pin;

public:
	inline constexpr Pin (Port& port, uint8_t pin) noexcept : port(port), pin(pin) {}

	inline void init() { port.initPins(1 << pin); }
	inline void close() noexcept { port.closePins(1 << pin); }
	inline bool isUsed() noexcept { return port.arePinsUsed(1 << pin); }

	inline void setOutput() noexcept { port.ddrReg |= (1 << pin); }
	inline void write(bool data) noexcept { if (data) port.portReg |= (1 << pin); else port.portReg &= ~(1 << pin); }
	inline void setHigh() noexcept { port.portReg |= (1 << pin); }
	inline void setLow() noexcept { port.portReg &= ~(1 << pin); }
	inline void toggle() noexcept { port.pinReg |= (1 << pin); }

	inline void setInput() noexcept { port.ddrReg &= ~(1 << pin); }
	inline bool read() noexcept { return port.pinReg & (1 << pin); }
	inline void setPullup(bool enable) noexcept { write(enable); }
	inline void enablePullup() noexcept { setHigh(); }
	inline void disablePullup() noexcept { setLow(); }
};


#endif /* SRC_RESOURCES_PERIPHERY_PIN_H_ */
