#ifndef SRC_RESOURCES_PERIPHERY_TIMER16BIT_H_
#define SRC_RESOURCES_PERIPHERY_TIMER16BIT_H_


#include <stdint.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"
#include "secondary/Pin.h"
#include <util/atomic.h>

//TODO: implement GTCCR functionalities (synchronisation)

//Forward Declarations
namespace Periphery {
	template <char Channel> inline Pin getTimer16bitCompareOutputPin(uint8_t timerIndex) noexcept;
	inline Pin getTimer16bitExternalClockPin(uint8_t timerIndex) noexcept;
}
namespace AddressMap {
	inline uint8_t getIdentity(const Timer16bit* periphery) noexcept;
	inline constexpr intptr_t getRegisterTIFR(uint8_t index) noexcept;
	inline constexpr intptr_t getRegisterTIMSK(uint8_t index) noexcept;
}

///Abstraction of the 8bit Timers
class Timer16bit {

public:

	///The TCCRnA register
	union TCCRA {
		struct FIELDS {
			volatile uint8_t dataWGM01 : 2; //Waveform generation mode control bits [0-1]
			volatile uint8_t dataCOMC : 2; 	//Compare output mode C
			volatile uint8_t dataCOMB : 2; 	//Compare output mode B
			volatile uint8_t dataCOMA : 2; 	//Compare output mode A
		} fields;
		volatile uint8_t reg;
	} regTCCRA;

	///The TCCRnB register
	union TCCRB {
		struct FIELDS {
			volatile uint8_t dataCS : 3; 	//Clock select
			volatile uint8_t dataWGM23 : 2; //Waveform generation mode control bits [2-3]
			volatile const uint8_t reserved : 1;
			volatile uint8_t flagICES : 1; 	//Input Capture Edge Select (1 = rising, 0 = falling)
			volatile uint8_t flagICNC : 1; 	//Input Capture Noise Canceler
		} fields;
		volatile uint8_t reg;
	} regTCCRB;

	///The TCCRnC register
	union TCCRC {
		struct FIELDS {
			volatile const uint8_t reserved : 5;
			volatile uint8_t flagFOCC : 1; 	//Force Output Compare for Channel C
			volatile uint8_t flagFOCB : 1; 	//Force Output Compare for Channel B
			volatile uint8_t flagFOCA : 1; 	//Force Output Compare for Channel A
		} fields;
		volatile uint8_t reg;
	} regTCCRC;

private:

	volatile const uint8_t reserved;

public:

	///The TCNTn register
	volatile uint16_t regTCNT; 	//Timer counter

	///The ICRn register
	volatile uint16_t regICR;	//Input Capture Register

	///The OCRnA register
	volatile uint16_t regOCRA; 	//Output Compare Register A

	///The OCRnA register
	volatile uint16_t regOCRB; 	//Output Compare Register B

	///The OCRnA register
	volatile uint16_t regOCRC; 	//Output Compare Register C

	///Enumeration to describe the Compare Output Mode (Read more in the µC's documentation)
	enum CompareOutputMode : uint8_t {
		DISCONNECTED = 0x00,
		TOGGLE = 0x01,
		CLEAR = 0x02,
		SET = 0x03
	};

	///Enumeration to describe the Waveform Generation Mode (Read more in the µC's documentation)
	enum WaveformGenerationMode : uint8_t {
		NORMAL = 0x00,
		PWM_FAST_0X00FF = 0x05,
		PWM_FAST_0X01FF = 0x06,
		PWM_FAST_0X03FF = 0x07,
		PWM_FAST_ICR = 0x0E,
		PWM_FAST_OCRA = 0x0F,
		PWM_PHASECORRECT_0X00FF = 0x01,
		PWM_PHASECORRECT_0X01FF = 0x02,
		PWM_PHASECORRECT_0X03FF = 0x03,
		PWM_PHASECORRECT_ICR = 0x0A,
		PWM_PHASECORRECT_OCRA = 0x0B,
		PWM_PHASECORRECT_FREQUENCYCORRECT_ICR = 0x08,
		PWM_PHASECORRECT_FREQUENCYCORRECT_OCRA = 0x09,
		CTC_OCRA = 0x04,
		CTC_ICR = 0x0C
	};

	///Enumeration to describe the Clock Selection Mode (Caution, some only work on synchronous/asynchronous Timers, Read more in the µC's documentation)
	enum ClockSelect : uint8_t {
		NONE = 0x00,
		PRESCALE_1 = 0x01,
		PRESCALE_8 = 0x02,
		PRESCALE_64 = 0x03,
		PRESCALE_256 = 0x04,
		PRESCALE_1024 = 0x05,
		EXTERNAL_FALLING = 0x06,
		EXTERNAL_RISING = 0x07
	};

private:

	///Runtime information about this Timer's number of Output Compare Channels
	static constexpr uint8_t ChannelCount = 3;

	///No Constructor to prohibit instantiation
	Timer16bit() = delete;

public:

	///Initializes the Timer16bit
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the Usart
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the Usart
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	///Gets the number of output compare channelCount of this Timer
	inline const uint8_t getChannelCount() const noexcept {
		return Timer16bit::ChannelCount;
	}

	///Gets the Pin connected to this Timer's compare output on the template-parameter specified channel.
	template <char Channel> inline Pin getCompareOutputPin() const noexcept {
		return Periphery::getTimer16bitCompareOutputPin<Channel>(AddressMap::getIdentity(this));
	}

	///Gets the Pin connected to this Timer's external clock input. Will not be auto-allocated by the Timer when used as clock source,
	///as it can be used as clock-input even when configured as output pin. This enables clock-generation via Software!
	inline Pin getExternalClockInputPin() const noexcept {
		return Periphery::getTimer16bitExternalClockPin(AddressMap::getIdentity(this));
	}

	//todo: implement input capture functions and interrupts...

	///Sets the Compare Output Mode of the the template-parameter specified channel.
	///(Pin must be set to 'Output' mode in order to enable the output driver!)
	template <char Channel> inline void setCompareOutputMode(CompareOutputMode mode) noexcept;

	///Sets the Waveform Generation Mode (Caution: Can start Timer!)
	inline void setWaveformGenerationMode(WaveformGenerationMode mode) noexcept {
		uint8_t wgm01 = (mode & 0x03);
		uint8_t wgm23 = (mode >> 2);
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			this->regTCCRA.fields.dataWGM01 = wgm01;
			this->regTCCRB.fields.dataWGM23 = wgm23;
		}
	}

	///Forces an Output Compare on the template-parameter specified channel.
	template <char Channel> inline void forceOutputCompare() noexcept;

	///Selects the Clock / Prescalar for this clock (Caution: Can start Timer!)
	inline void setClockSelect(ClockSelect mode) noexcept {
		this->regTCCRB.fields.dataCS = mode;
	}

	///Reads the current Timer Counter value
	inline uint16_t getCounterValue() const noexcept { return this->regTCNT; }

	///Writes the current Timer Counter value
	inline void setCounterValue(uint16_t counter) noexcept { this->regTCNT = counter; }

	///Reads the current Input Capture value
	inline uint16_t getInputCaptureValue() const noexcept { return this->regICR; }

	///Writes the current Input Capture value
	inline void setInputCaptureValue(uint16_t value) noexcept { this->regICR = value; }

	///Reads the Output Compare Value of the template-parameter specified channel.
	template <char Channel> inline uint16_t getOutputCompareValue() const noexcept;

	///Writes the Output Compare Value of the template-parameter specified channel.
	template <char Channel> inline void setOutputCompareValue(uint16_t value) noexcept;

	///Enables the Output Compare Match Interrupt of the template-parameter specified channel.
	template <char Channel> inline void enableOutputCompareMatchInterrupt() const noexcept;

	///Disables the Output Compare Match Interrupt of the template-parameter specified channel.
	template <char Channel> inline void disableOutputCompareMatchInterrupt() const noexcept;

	///Enables the Timer Overflow Interrupt.
	inline void enableTimerOverflowInterrupt() const noexcept {
		uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
		*regTIMSK |= 0x01;
	}

	///Disables the Timer Overflow Interrupt.
	inline void disableTimerOverflowInterrupt() const noexcept {
		uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
		*regTIMSK &= ~0x01;
	}
};

//Implementations of Member-Specializations
template <> inline void Timer16bit::setCompareOutputMode<'A'>(CompareOutputMode mode) noexcept {
	if (Configuration::autoPinAllocationEnabled || Configuration::autoPinConfigurationEnabled) {
		Pin out = this->getCompareOutputPin<'A'>();
		uint8_t currentMode = this->regTCCRA.fields.dataCOMA;
		if (currentMode == CompareOutputMode::DISCONNECTED && mode != CompareOutputMode::DISCONNECTED) {
			if (Configuration::autoPinAllocationEnabled) {
				out.init(); //TODO: Deal with possible exception!
			}
			if (Configuration::autoPinConfigurationEnabled) {
				out.setMode(Pin::Mode::OUTPUT);
			}
		}
		else if (currentMode != CompareOutputMode::DISCONNECTED && mode == CompareOutputMode::DISCONNECTED) {
			if (Configuration::autoPinAllocationEnabled) {
				out.close();
			}
			if (Configuration::autoPinConfigurationEnabled) {
				out.setMode(Pin::Mode::INPUT);
			}
		}
	}
	this->regTCCRA.fields.dataCOMA = mode;
}
template <> inline void Timer16bit::setCompareOutputMode<'B'>(CompareOutputMode mode) noexcept {
	if (Configuration::autoPinAllocationEnabled || Configuration::autoPinConfigurationEnabled) {
		Pin out = this->getCompareOutputPin<'B'>();
		uint8_t currentMode = this->regTCCRA.fields.dataCOMB;
		if (currentMode == CompareOutputMode::DISCONNECTED && mode != CompareOutputMode::DISCONNECTED) {
			if (Configuration::autoPinAllocationEnabled) {
				out.init(); //TODO: Deal with possible exception!
			}
			if (Configuration::autoPinConfigurationEnabled) {
				out.setMode(Pin::Mode::OUTPUT);
			}
		}
		else if (currentMode != CompareOutputMode::DISCONNECTED && mode == CompareOutputMode::DISCONNECTED) {
			if (Configuration::autoPinAllocationEnabled) {
				out.close();
			}
			if (Configuration::autoPinConfigurationEnabled) {
				out.setMode(Pin::Mode::INPUT);
			}
		}
	}
	this->regTCCRA.fields.dataCOMB = mode;
}
template <> inline void Timer16bit::setCompareOutputMode<'C'>(CompareOutputMode mode) noexcept {
	if (Configuration::autoPinAllocationEnabled || Configuration::autoPinConfigurationEnabled) {
		Pin out = this->getCompareOutputPin<'C'>();
		uint8_t currentMode = this->regTCCRA.fields.dataCOMC;
		if (currentMode == CompareOutputMode::DISCONNECTED && mode != CompareOutputMode::DISCONNECTED) {
			if (Configuration::autoPinAllocationEnabled) {
				out.init(); //TODO: Deal with possible exception!
			}
			if (Configuration::autoPinConfigurationEnabled) {
				out.setMode(Pin::Mode::OUTPUT);
			}
		}
		else if (currentMode != CompareOutputMode::DISCONNECTED && mode == CompareOutputMode::DISCONNECTED) {
			if (Configuration::autoPinAllocationEnabled) {
				out.close();
			}
			if (Configuration::autoPinConfigurationEnabled) {
				out.setMode(Pin::Mode::INPUT);
			}
		}
	}
	this->regTCCRA.fields.dataCOMC = mode;
}
template <> inline void Timer16bit::forceOutputCompare<'A'>() noexcept {
	this->regTCCRC.fields.flagFOCA = 1;
}
template <> inline void Timer16bit::forceOutputCompare<'B'>() noexcept {
	this->regTCCRC.fields.flagFOCB = 1;
}
template <> inline void Timer16bit::forceOutputCompare<'C'>() noexcept {
	this->regTCCRC.fields.flagFOCC = 1;
}
template <> inline uint16_t Timer16bit::getOutputCompareValue<'A'>() const noexcept {
	return this->regOCRA;
}
template <> inline uint16_t Timer16bit::getOutputCompareValue<'B'>() const noexcept {
	return this->regOCRB;
}
template <> inline uint16_t Timer16bit::getOutputCompareValue<'C'>() const noexcept {
	return this->regOCRC;
}
template <> inline void Timer16bit::setOutputCompareValue<'A'>(uint16_t value) noexcept {
	this->regOCRA = value;
}
template <> inline void Timer16bit::setOutputCompareValue<'B'>(uint16_t value) noexcept {
	this->regOCRB = value;
}
template <> inline void Timer16bit::setOutputCompareValue<'C'>(uint16_t value) noexcept {
	this->regOCRC = value;
}
template <> inline void Timer16bit::enableOutputCompareMatchInterrupt<'A'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
	*regTIMSK |= (0x01<<1);
}
template <> inline void Timer16bit::enableOutputCompareMatchInterrupt<'B'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
	*regTIMSK |= (0x01<<2);
}
template <> inline void Timer16bit::enableOutputCompareMatchInterrupt<'C'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
	*regTIMSK |= (0x01<<3);
}
template <> inline void Timer16bit::disableOutputCompareMatchInterrupt<'A'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
	*regTIMSK &= ~(0x01<<1);
}
template <> inline void Timer16bit::disableOutputCompareMatchInterrupt<'B'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
	*regTIMSK &= ~(0x01<<2);
}
template <> inline void Timer16bit::disableOutputCompareMatchInterrupt<'C'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(AddressMap::getIdentity(this)));
	*regTIMSK &= ~(0x01<<3);
}


#endif /* SRC_RESOURCES_PERIPHERY_TIMER16BIT_H_ */
