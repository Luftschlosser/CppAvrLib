#ifndef SRC_RESOURCES_PERIPHERY_ADC_H_
#define SRC_RESOURCES_PERIPHERY_ADC_H_


#include <stdint.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


//Forward Declarations
namespace Periphery {
//	inline Pin getTwiSclPin() noexcept;
//	inline Pin getTwiSdaPin() noexcept;
}


///MMIO Abstraction of the ADCs
class Adc final {

private:

	///No Constructor to prohibit instantiation
	Adc() = delete;

public:

	///The ADCL + ADCH registers
	volatile uint16_t ADCreg;

	///The ADCSRA register
	union ADCSRAreg {
		struct FIELDS {
			volatile uint8_t dataADPS : 3; //ADC Prescaler Select Bits
			volatile uint8_t flagADIE : 1; //ADC Interrupt Enable
			volatile uint8_t flagADIF : 1; //ADC Interrupt Flag
			volatile uint8_t flagADATE: 1; //ADC Auto Trigger Enable
			volatile uint8_t flagADSC : 1; //ADC Start Conversion
			volatile uint8_t flagADEN : 1; //ADC Enable
		} fields;
		volatile uint8_t reg;
	} regADCSRA;

	///The ADCSRB register
	union ADCSRBreg {
		struct FIELDS {
			volatile uint8_t dataADTS : 3; //ADC Auto Trigger Source
			volatile uint8_t flagMUX5 : 1; //Analog Channel and Gain Selection Bit5. CAUTION: Does not exist on all AVR ATmega's
			volatile const uint8_t reserved : 2;
			volatile const uint8_t flagACME : 1; //Undocumented
		} fields;
		volatile uint8_t reg;
	} regADCSRB;

	///The ADMUX register
	union ADMUXreg {
		struct FIELDS {
			volatile uint8_t dataMUX : 5; //Analog Channel Selection Bits. CAUTION: Only 4 bit long on some AVR ATmega's
			volatile uint8_t flagADLAR : 1; //ADC Left Adjust Result
			volatile uint8_t dataREFS : 2; //Reference Selection Bits
		} fields;
		volatile uint8_t reg;
	} regADMUX;

	///The DIDR2 register. CAUTION: Does not exist on all AVR ATmega's
	volatile uint8_t DIDR2reg;

	///The DIDR0 register
	volatile uint8_t DIDR0reg;


	///Initializes the Adc
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the Adc
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the Adc
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_ADC_H_ */
