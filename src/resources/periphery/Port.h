#ifndef SRC_RESOURCES_PERIPHERY_PORT_H_
#define SRC_RESOURCES_PERIPHERY_PORT_H_


#include <stdint.h>
#include "../Periphery.h"


class Pin;


class Port final {
	friend Pin;
	friend Periphery;

private:
	volatile uint8_t pinReg; //PINn
	volatile uint8_t ddrReg; //DDRn
	volatile uint8_t portReg; //PORTn

	static uint8_t usage[Periphery::getCapacity<Port>()];

	inline Port() noexcept {}

	void initPins(uint8_t mask);
	void closePins(uint8_t mask) noexcept;
	bool arePinsUsed(uint8_t mask) noexcept;

public:
	void init();
	void close() noexcept;
	bool isUsed() noexcept;

	inline void setOutput() noexcept { ddrReg = 0xFF; }
	inline void writeOutput(uint8_t data) noexcept { portReg = data; }
	inline uint8_t readOutput() noexcept { return portReg; }
	inline void toggleOutput() noexcept { pinReg = 0xFF; }
	inline void toggleOutput(uint8_t toggleMask) noexcept { pinReg = toggleMask; }

	inline void setInput() noexcept { ddrReg = 0; }
	inline uint8_t readInput() noexcept { return pinReg; }
	inline void writeInputPullups(uint8_t mask) noexcept { portReg = mask; }
	inline uint8_t readInputPullups() noexcept { return portReg; }

	inline void writeDataDirections(uint8_t directionMask) noexcept { ddrReg = directionMask; }
	inline uint8_t readDataDirections() noexcept { return ddrReg; }
};


#endif /* SRC_RESOURCES_PERIPHERY_PORT_H_ */
