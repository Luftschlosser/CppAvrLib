#ifndef SRC_RESOURCES_PERIPHERY_EEPROM_H_
#define SRC_RESOURCES_PERIPHERY_EEPROM_H_


#include <stdint.h>
#include <util/atomic.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


///MMIO Abstraction of the Eeprom Memory
class Eeprom final {

private:

	///No Constructor to prohibit instantiation
	Eeprom() = delete;

public:

	///The EECR register
	union EECRreg {
		struct FIELDS {
			volatile uint8_t flagEERE : 1; //Eeprom Read Enable
			volatile uint8_t flagEEPE : 1; //Eeprom Programming Enable
			volatile uint8_t flagEEMPE : 1; //Eeprom Master Programming Enable
			volatile uint8_t flagEERIE: 1; //Eeprom Ready Interrupt Enable
			volatile uint8_t dataEEPM : 2; //Eeprom Programming Mode
			const volatile uint8_t unused : 2;
		} fields;
		volatile uint8_t reg;
	} controlReg;

	///The EEDR register
	volatile uint8_t dataReg;

	///The EEAR register
	volatile uint16_t adrReg;

	//Prescale Value to determine the AdcClock (based on F_CPU)
	enum ProgrammingMode : uint8_t {
		EraseAndWrite = 0,
		EraseOnly = 1,
		WriteOnly = 2
	};


	///Initializes the Eeprom
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the Eeprom
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the Eeprom
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	inline uint8_t read(uint16_t address) noexcept {
		this->adrReg = address;
		this->controlReg.fields.flagEERE = 1;
		return this->dataReg;
	}

	inline void setProgrammingMode(ProgrammingMode programmingMode) noexcept {
		this->controlReg.fields.dataEEPM = programmingMode;
	}

	inline void enableInterrupt() noexcept {
		this->controlReg.fields.flagEERIE = 1;
	}

	inline void disableInterrupt() noexcept {
		this->controlReg.fields.flagEERIE = 0;
	}

	inline bool isWriting() noexcept {
		return this->controlReg.fields.dataEEPM == 1;
	}

	inline void writeAsync(uint16_t address, uint8_t data) noexcept {
		uint8_t ctrlBuf = this->controlReg.reg & 0xF8; //Clear EERE & EEPE & EEMPE
		this->adrReg = address;
		this->dataReg = data;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			this->controlReg.reg = (ctrlBuf | (1<<2)); //Write EEMPE to 1, EEPE to 0
			this->controlReg.reg |= (1<<1); //Set EEPE to 1
		}
	}

	inline void writeSync(uint16_t address, uint8_t data) noexcept {
		this->writeAsync(address, data);
		while (this->isWriting());
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_EEPROM_H_ */
