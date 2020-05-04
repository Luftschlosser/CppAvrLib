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

	inline void init() const { port.initPins(1 << pin); }
	inline void close() const noexcept { port.closePins(1 << pin); }
	inline bool isUsed() const noexcept { return port.arePinsUsed(1 << pin); }

	inline void setOutput() const noexcept { port.regDDR |= (1 << pin); }
	inline void write(bool data) const noexcept { if (data) port.regPORT |= (1 << pin); else port.regPORT &= ~(1 << pin); }
	inline void setHigh() const noexcept { port.regPORT |= (1 << pin); }
	inline void setLow() const noexcept { port.regPORT &= ~(1 << pin); }
	inline void toggle() const noexcept { port.regPIN |= (1 << pin); }

	inline void setInput() const noexcept { port.regDDR &= ~(1 << pin); }
	inline bool read() const noexcept { return port.regPIN & (1 << pin); }
	inline void setPullup(bool enable) const noexcept { write(enable); }
	inline void enablePullup() const noexcept { setHigh(); }
	inline void disablePullup() const noexcept { setLow(); }
};


#endif /* SRC_RESOURCES_PERIPHERY_PIN_H_ */
