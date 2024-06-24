#ifndef SRC_RESOURCES_PERIPHERY_WATCHDOG_H_
#define SRC_RESOURCES_PERIPHERY_WATCHDOG_H_


#include <stdint.h>
#include <util/atomic.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


///MMIO Abstraction of the Watchdog
class Watchdog final {
private:

	///No Constructor to prohibit instantiation
	Watchdog() = delete;

	inline void enableChange() noexcept {
		this->regWDTCSR.reg = 0x18;	//WDCE | WDE
	}

public:

	///The WDTCSR register
	union WatchdogCtrlReg {
		struct FIELDS {
			volatile uint8_t dataWDP02 : 3;	//Watchdog Timer Prescaler Bits 2, 1 and 0
			volatile uint8_t flagWDE  : 1;	//Watchdog System Reset Enable
			volatile uint8_t flagWDCE : 1;	//Watchdog Change Enable
			volatile uint8_t flagWDP3 : 1;	//Watchdog Timer Prescaler Bit 3
			volatile uint8_t flagWDIE : 1;	//Watchdog Interrupt Enable
			volatile uint8_t flagWDIF : 1;	//Watchdog Interrupt Flag
		} fields;
		volatile uint8_t reg = 0;

		enum Prescaler : uint8_t {
			Timeout16ms = 0x00,
			Timeout32ms = 0x01,
			Timeout64ms = 0x02,
			Timeout128ms = 0x03,
			Timeout256ms = 0x04,
			Timeout512ms = 0x05,
			Timeout1s = 0x06,
			Timeout2s = 0x07,
			Timeout4s = 0x20,
			Timeout8s = 0x21
		};
	} regWDTCSR;


	///Initializes the Watchdog
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the Watchdog
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the Watchdog
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	inline void configure(WatchdogCtrlReg::Prescaler prescale, bool interruptEnable, bool resetEnable) noexcept {
		volatile WatchdogCtrlReg buf;
		buf.reg |= prescale;
		buf.fields.flagWDIE = interruptEnable ? 1 : 0;
		buf.fields.flagWDE = resetEnable ? 1 : 0;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			this->enableChange();
			this->regWDTCSR.reg = buf.reg;
		}
	}

	inline void disable() noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			this->enableChange();
			this->regWDTCSR.reg = 0;
		}
	}

	inline void resetTimeout() noexcept {
		__asm__ __volatile__ ("wdr");
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_WATCHDOG_H_ */
