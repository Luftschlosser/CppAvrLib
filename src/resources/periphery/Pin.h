#ifndef SRC_RESOURCES_PERIPHERY_PIN_H_
#define SRC_RESOURCES_PERIPHERY_PIN_H_


#include <stdint.h>
#include "Port.h"


class Pin {

private:
	Port* port;
	uint8_t mask;

public:
	inline Pin (Port* port, uint8_t pin) noexcept : port(port), mask(0) { mask = (1 << pin); }

	inline void init() { port->initPins(mask); }
	inline void close() noexcept { port->closePins(mask); }
	inline bool isUsed() noexcept { return port->arePinsUsed(mask); }

	inline void setOutput() noexcept { port->ddrReg |= mask; }
	inline void write(bool data) noexcept { if (data) port->portReg |= mask; else port->portReg &= ~mask; }
	inline void setHigh() noexcept { port->portReg |= mask; }
	inline void setLow() noexcept { port->portReg &= ~mask; }
	inline void toggle() noexcept { port->pinReg = mask; }

	inline void setInput() noexcept { port->ddrReg &= ~mask; }
	inline bool read() noexcept { return port->pinReg & mask; }
	inline void setPullup(bool enable) noexcept { write(enable); }
	inline void enablePullup() noexcept { setHigh(); }
	inline void disablePullup() noexcept { setLow(); }
};


#endif /* SRC_RESOURCES_PERIPHERY_PIN_H_ */
