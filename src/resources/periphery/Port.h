#ifndef SRC_RESOURCES_PERIPHERY_PORT_H_
#define SRC_RESOURCES_PERIPHERY_PORT_H_


#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


///MMIO Abstraction of the GPIO Ports
class Port final {

private:

	///No Constructor to prohibit instantiation
	Port() = delete;

public:

	///The PINn register
	volatile uint8_t regPIN;

	///The DDRn register
	volatile uint8_t regDDR;

	///The PORTn register
	volatile uint8_t regPORT;

	///Enumeration to describe the mode of operation
	enum Mode : uint8_t {
		OUTPUT,
		INPUT,
		INPUT_PULLUP
	};

	///Initializes the entire Port
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///Initializes a part of this Port
	///\param mask the bitmask which specifies the bits to allocate (1 = allocate)
	inline void init(uint8_t mask) const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this, mask)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the entire Port
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///De-Initializes part of this Port
	///\param mask the bitmask which specifies the bits to de-allocate (1 = de-allocate)
	inline void close(uint8_t mask) const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this, mask);
		}
	}

	///checks the usage of the Port
	///\return true if at least one Pin of the Port is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	///checks the usage of the Port
	///\return true if at least one of the specified Pins of the Port is already in use, else false
	///\param mask the bitmask which specifies the bits to check (1 = check)
	inline bool isUsed(uint8_t mask) const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this, mask);
		}
		else {
			return false;
		}
	}


	///Sets the mode of operation for the entire Port
	///\param mode the mode of operation to configure
	inline void setMode(Mode mode) noexcept {
		switch (mode) {
		case Mode::OUTPUT:
			regDDR = 0xFF;
			break;
		case Mode::INPUT:
			regDDR = 0x00;
			regPORT = 0x00;
			break;
		case Mode::INPUT_PULLUP:
			regDDR = 0x00;
			regPORT = 0xFF;
			break;
		}
	}

	///Writes data to the Port (in Output mode)
	///\param data the byte to write to the port
	inline void write(uint8_t data) noexcept { regPORT = data; }

	///Toggles all Bits of the Port (in Output mode)
	inline void toggle() noexcept { regPIN = 0xFF; }

	///Reads data from the Port (in Input mode)
	///return the byte which is currently on the port
	inline uint8_t read() const noexcept { return regPIN; }
};


#endif /* SRC_RESOURCES_PERIPHERY_PORT_H_ */
