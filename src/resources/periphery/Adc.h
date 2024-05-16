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

			//Prescale Value to determine the AdcClock (based on F_CPU)
			enum Prescalar : uint8_t {
				Scale2 = 1,
				Scale4 = 2,
				Scale8 = 3,
				Scale16 = 4,
				Scale32 = 5,
				Scale64 = 6,
				Scale128 = 7
			};
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

			///The reference Voltage Source to use for conversions
			enum Reference : uint8_t {
				AREF = 0,
				AVCC = 1,
				Internal1 = 2, //Not available on m328p, 1,1V on m2560
				Internal2 = 3  //1,1V on m328p, 2,56V on m2560
			};
		} fields;
		volatile uint8_t reg;
	} regADMUX;

	///The DIDR2 register. CAUTION: Does not exist on all AVR ATmega's
	volatile uint8_t DIDR2reg;

	///The DIDR0 register
	volatile uint8_t DIDR0reg;


	//Trigger Source/RunningMode for ADC
	enum TriggerSource : uint8_t {
		SingleConversion = 8,
		FreeRunning = 0,
		AnalogComparator = 1,
		ExternalInterrupt0 = 2,
		Timer0_CompareMatchA = 3,
		Timer0_Overflow = 4,
		Timer1_CompareMatchB = 5,
		Timer1_Overflow = 6,
		Timer1_InputCapture = 7
	};


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

	inline uint16_t readValue() const noexcept {
		return this->ADCreg;
	}

	inline void setPrescale(ADCSRAreg::FIELDS::Prescalar scale) noexcept {
		this->regADCSRA.fields.dataADPS = scale;
	}

	///Sets the prescale to the lowest value which allows maximum precision at current F_CPU
	inline void setPrescaleAuto() noexcept {
		static constexpr uint8_t f_max = 200000;
		uint8_t scale;
		for (scale = 1; (F_CPU >> scale) > f_max; scale++);
		this->regADCSRA.fields.dataADPS = scale;
	}

	inline void enable() noexcept {
		this->regADCSRA.fields.flagADEN = 1;
	}

	inline void disable() noexcept {
		this->regADCSRA.fields.flagADEN = 0;
	}

	inline void enableInterrupt() noexcept {
		this->regADCSRA.fields.flagADIE = 1;
	}

	inline void disableInterrupt() noexcept {
		this->regADCSRA.fields.flagADIE = 0;
	}

	inline void clearInterruptFlag() noexcept {
		this->regADCSRA.fields.flagADIF = 1;
	}

	inline void setTriggerSource(TriggerSource source) noexcept {
		if (source == TriggerSource::SingleConversion) {
			this->regADCSRA.fields.flagADATE = 0;
		}
		else {
			this->regADCSRA.fields.flagADATE = 1;
			this->regADCSRB.fields.dataADTS = source;
		}
	}

	inline void startConversion() noexcept {
		this->regADCSRA.fields.flagADSC = 1;
	}

	inline void setReferenceSource(ADMUXreg::FIELDS::Reference source) noexcept {
		this->regADMUX.fields.dataREFS = source;
	}

	inline void setLeftAdjustResult(bool leftAdjust = true) noexcept {
		if (leftAdjust) {
			this->regADMUX.fields.flagADLAR = 1;
		}
		else {
			this->regADMUX.fields.flagADLAR = 0;
		}
	}

	inline void setMuxValue(uint8_t value) noexcept {
		if (Periphery::AdcNumberOfMuxOptions <= 32) {
			this->regADMUX.fields.dataMUX = (value & (Periphery::AdcNumberOfMuxOptions - 1));
		}
		else {
			this->regADMUX.fields.dataMUX = (value & 0x1f);
			this->regADCSRB.fields.flagMUX5 = (value >> 5);
		}
	}

	inline void disableDigitalInput(uint16_t channel) noexcept {
		if (channel < Periphery::AdcChannelCount) {
			if (channel < 8) {
				this->DIDR0reg |= 1<<channel;
			}
			else {
				this->DIDR2reg |= 1<<(channel-8);
			}
		}
	}

	inline void disableDigitalInputs(uint8_t mask) noexcept {
		this->DIDR0reg = mask;
	}

	inline void disableDigitalInputs(uint16_t mask) noexcept {
		this->DIDR0reg = mask && 0xFF;
		this->DIDR2reg = mask >> 8;
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_ADC_H_ */
