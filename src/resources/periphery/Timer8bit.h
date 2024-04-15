#ifndef SRC_RESOURCES_PERIPHERY_TIMER8BIT_H_
#define SRC_RESOURCES_PERIPHERY_TIMER8BIT_H_


#include <stdint.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"
#include "secondary/Pin.h"
#include <util/atomic.h>


//TODO: implement GTCCR functionalities (synchronisation)


//Forward Declarations
class Timer8bitAsync;
namespace Periphery {
	template <uint8_t Index> inline Timer8bit getTimer8bit() noexcept;
	template <char Channel> inline Pin getTimer8bitCompareOutputPin(uint8_t timerIndex) noexcept;
	inline Pin getTimer8bitExternalClockPin(uint8_t timerIndex) noexcept;
}
namespace AddressMap {
	inline constexpr intptr_t getRegisterTIFR(uint8_t index) noexcept;
	inline constexpr intptr_t getRegisterTIMSK(uint8_t index) noexcept;
}


///Abstraction of the 8bit Timers
class Timer8bit {
	template <uint8_t Index> friend inline Timer8bit Periphery::getTimer8bit() noexcept;
	friend bool RuntimeAllocator::allocate(const Timer8bit* object) noexcept;
	friend void RuntimeAllocator::deallocate(const Timer8bit* object) noexcept;
	friend bool RuntimeAllocator::isAllocated(const Timer8bit* object) noexcept;

public:

	///MMIO Abstraction of the registers (Inner class)
	class Registers final {
		friend Timer8bitAsync; //Allow only async timers to access ASSR register

	private:

		///No Constructor to prohibit instantiation
		Registers() = delete;

	public:

		///The TCCRnA register
		union TCCRA {
			struct FIELDS {
				volatile uint8_t dataWGM01 : 2; //Waveform generation mode control bits [0-1]
				volatile const uint8_t reserved : 2;
				volatile uint8_t dataCOMB : 2; //Compare output mode B
				volatile uint8_t dataCOMA : 2; //Compare output mode A
			} fields;
			volatile uint8_t reg;
		} volatile regTCCRA;

		///The TCCRnB register
		union TCCRB {
			struct FIELDS {
				volatile uint8_t dataCS : 3; //Clock select
				volatile uint8_t flagWGM2 : 1; //Waveform generation mode control bit [2]
				volatile const uint8_t reserved : 2;
				volatile uint8_t flagFOCB : 1; //Force output compare B
				volatile uint8_t flagFOCA : 1; //Force output compare A
			} fields;
			volatile uint8_t reg;
		} volatile regTCCRB;

		///The TCNTn register
		volatile uint8_t regTCNT; //Timer counter

		///The OCRnA register
		volatile uint8_t regOCRA; //Output compare A

		///The OCRnB register
		volatile uint8_t regOCRB; //Output compare B

	private:

		volatile const uint8_t reserved;

		///The ASSR register (only available for async timers)
		union ASSR_REGISTER {
			struct FIELDS {
				volatile const uint8_t flagTCRBUB : 1; //Update busy flag for TCCRnB register
				volatile const uint8_t flagTCRAUB : 1; //Update busy flag for TCCRnA register
				volatile const uint8_t flagOCRBUB : 1; //Update busy flag for OCRnB register
				volatile const uint8_t flagOCRAUB : 1; //Update busy flag for OCRnA register
				volatile const uint8_t flagTCNUB : 1;  //Update busy flag for TCNT register
				volatile uint8_t flagAS : 1; //Asynchronous operation flag
				volatile uint8_t flagEXCLK : 1; //External clock flag
				volatile const uint8_t reserved : 1;
			} fields;
			volatile uint8_t reg;
		} volatile regASSR;
	};

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
		CTC = 0x02,
		PWM_FAST_0XFF = 0x03,
		PWM_FAST_OCRA = 0x07,
		PWM_PHASECORRECT_0XFF = 0x01,
		PWM_PHASECORRECT_OCRA = 0x05
	};

	///Enumeration to describe the Clock Selection Mode (Caution, some only work on synchronous/asynchronous Timers, Read more in the µC's documentation)
	enum ClockSelect : uint8_t {
		NONE,
		PRESCALE_1,
		PRESCALE_8,
		PRESCALE_32a, 	//Only available on asynchronous Timer
		PRESCALE_64,
		PRESCALE_128a, 	//Only available on asynchronous Timer
		PRESCALE_256,
		PRESCALE_1024,
		EXTERNAL_FALLING, 	//Only available on synchronous Timer
		EXTERNAL_RISING 	//Only available on synchronous Timer
	};

	///Reference to the MMIO control registers of the Timer
	Registers& registers;

private:

	///Runtime information about this Timer's type (asynchronous or synchronous)
	const uint8_t asynchronous : 1; //flag to avoid virtual functions for clock select

	///Runtime information about this Timer's identity
	const uint8_t timerIndex : 7; //doesn't need address-based identity-function that way

	///Runtime information about this Timer's number of Output Compare Channels
	static constexpr uint8_t ChannelCount = 2;

protected:

	///Constructor (friend periphery-function to create instance)
	inline constexpr Timer8bit (Registers& registers, uint8_t timerIndex, bool async) noexcept :
			registers(registers), asynchronous(async ? 1 : 0), timerIndex(timerIndex) {}

public:

	///Destructor
	inline ~Timer8bit() noexcept = default;

	///Initializes the Timer
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the Timer
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the Timer
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	///Checks if this Timer8bit object happens to be an asynchronous timer (not the current mode, only the capability)
	inline bool isAsyncTimer() const noexcept {
		return this->asynchronous == 1;
	}

	///Gets the number of output compare channelCount of this Timer
	inline constexpr uint8_t getChannelCount() const noexcept {
		return Timer8bit::ChannelCount;
	}

	///Gets the Pin connected to this Timer's compare output on the template-parameter specified channel.
	template <char Channel> inline Pin getCompareOutputPin() const noexcept {
		return Periphery::getTimer8bitCompareOutputPin<Channel>(this->timerIndex);
	}

	///Gets the Pin connected to this Timer's external clock input. Will not be auto-allocated by the Timer when used as clock source,
	///as it can be used as clock-input even when configured as output pin. This enables clock-generation via Software!
	inline Pin getExternalClockInputPin() const noexcept {
		return Periphery::getTimer8bitExternalClockPin(this->timerIndex);
	}

	///Sets the Compare Output Mode of the the template-parameter specified channel.
	///(Pin must be set to 'Output' mode in order to enable the output driver!)
	template <char Channel> inline void setCompareOutputMode(CompareOutputMode mode) const noexcept;

	///Sets the Waveform Generation Mode (Caution: Can start Timer!)
	inline void setWaveformGenerationMode(WaveformGenerationMode mode) const noexcept {
		uint8_t wgm01 = (mode & 0x03);
		uint8_t wgm2 = (mode > 0x03) ? 1 : 0;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			this->registers.regTCCRA.fields.dataWGM01 = wgm01;
			this->registers.regTCCRB.fields.flagWGM2 = wgm2;
		}
	}

	///Forces an Output Compare on the template-parameter specified channel.
	template <char Channel> inline void forceOutputCompare() const noexcept;

	///Selects the Clock / Prescalar for this clock (Caution: Can start Timer!)
	inline void setClockSelect(ClockSelect mode) const {
		if (isAsyncTimer()) {
			switch (mode) {
			case NONE:
				this->registers.regTCCRB.fields.dataCS = 0x00;
				break;
			case PRESCALE_1:
				this->registers.regTCCRB.fields.dataCS = 0x01;
				break;
			case PRESCALE_8:
				this->registers.regTCCRB.fields.dataCS = 0x02;
				break;
			case PRESCALE_32a:
				this->registers.regTCCRB.fields.dataCS = 0x03;
				break;
			case PRESCALE_64:
				this->registers.regTCCRB.fields.dataCS = 0x04;
				break;
			case PRESCALE_128a:
				this->registers.regTCCRB.fields.dataCS = 0x05;
				break;
			case PRESCALE_256:
				this->registers.regTCCRB.fields.dataCS = 0x06;
				break;
			case PRESCALE_1024:
				this->registers.regTCCRB.fields.dataCS = 0x07;
				break;
			default:
				//TODO: throw
				break;
			}
		}
		else {
			switch (mode) {
			case NONE:
				this->registers.regTCCRB.fields.dataCS = 0x00;
				break;
			case PRESCALE_1:
				this->registers.regTCCRB.fields.dataCS = 0x01;
				break;
			case PRESCALE_8:
				this->registers.regTCCRB.fields.dataCS = 0x02;
				break;
			case PRESCALE_64:
				this->registers.regTCCRB.fields.dataCS = 0x03;
				break;
			case PRESCALE_256:
				this->registers.regTCCRB.fields.dataCS = 0x04;
				break;
			case PRESCALE_1024:
				this->registers.regTCCRB.fields.dataCS = 0x05;
				break;
			case EXTERNAL_FALLING:
				this->registers.regTCCRB.fields.dataCS = 0x06;
				break;
			case EXTERNAL_RISING:
				this->registers.regTCCRB.fields.dataCS = 0x07;
				break;
			default:
				//TODO: throw
				break;
			}
		}
	}

	///Reads the current Timer Counter value
	inline uint8_t getCounterValue() const noexcept { return this->registers.regTCNT; }

	///Writes the current Timer Counter value
	inline void setCounterValue(uint8_t counter) const noexcept { this->registers.regTCNT = counter; }

	///Reads the Output Compare Value of the template-parameter specified channel.
	template <char Channel> inline uint8_t getOutputCompareValue() const noexcept;

	///Writes the Output Compare Value of the template-parameter specified channel.
	template <char Channel> inline void setOutputCompareValue(uint8_t value) const noexcept;

	///Enables the Output Compare Match Interrupt of the template-parameter specified channel.
	template <char Channel> inline void enableOutputCompareMatchInterrupt() const noexcept;

	///Disables the Output Compare Match Interrupt of the template-parameter specified channel.
	template <char Channel> inline void disableOutputCompareMatchInterrupt() const noexcept;

	///Enables the Timer Overflow Interrupt.
	inline void enableTimerOverflowInterrupt() const noexcept {
		uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(this->timerIndex));
		*regTIMSK |= 0x01;
	}

	///Disables the Timer Overflow Interrupt.
	inline void disableTimerOverflowInterrupt() const noexcept {
		uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(this->timerIndex));
		uint8_t* regTIFR = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIFR(this->timerIndex));
		*regTIMSK &= ~0x01;
		*regTIFR |= 0x01; //Clear any pending Interrupt Flag
	}
};


//Implementations of Member-Specializations
template <> inline void Timer8bit::setCompareOutputMode<'A'>(CompareOutputMode mode) const noexcept {
	if (Configuration::autoPinAllocationEnabled || Configuration::autoPinConfigurationEnabled) {
		Pin out = this->getCompareOutputPin<'A'>();
		uint8_t currentMode = this->registers.regTCCRA.fields.dataCOMA;
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
	this->registers.regTCCRA.fields.dataCOMA = mode;
}
template <> inline void Timer8bit::setCompareOutputMode<'B'>(CompareOutputMode mode) const noexcept {
	if (Configuration::autoPinAllocationEnabled || Configuration::autoPinConfigurationEnabled) {
		Pin out = this->getCompareOutputPin<'B'>();
		uint8_t currentMode = this->registers.regTCCRA.fields.dataCOMB;
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
	this->registers.regTCCRA.fields.dataCOMB = mode;
}
template <> inline void Timer8bit::forceOutputCompare<'A'>() const noexcept {
	this->registers.regTCCRB.fields.flagFOCA = 1;
}
template <> inline void Timer8bit::forceOutputCompare<'B'>() const noexcept {
	this->registers.regTCCRB.fields.flagFOCB = 1;
}
template <> inline uint8_t Timer8bit::getOutputCompareValue<'A'>() const noexcept {
	return this->registers.regOCRA;
}
template <> inline uint8_t Timer8bit::getOutputCompareValue<'B'>() const noexcept {
	return this->registers.regOCRB;
}
template <> inline void Timer8bit::setOutputCompareValue<'A'>(uint8_t value) const noexcept {
	this->registers.regOCRA = value;
}
template <> inline void Timer8bit::setOutputCompareValue<'B'>(uint8_t value) const noexcept {
	this->registers.regOCRB = value;
}
template <> inline void Timer8bit::enableOutputCompareMatchInterrupt<'A'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(this->timerIndex));
	*regTIMSK |= (0x01<<1);
}
template <> inline void Timer8bit::enableOutputCompareMatchInterrupt<'B'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(this->timerIndex));
	*regTIMSK |= (0x01<<2);
}
template <> inline void Timer8bit::disableOutputCompareMatchInterrupt<'A'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(this->timerIndex));
	uint8_t* regTIFR = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIFR(this->timerIndex));
	*regTIMSK &= ~(0x01<<1);
	*regTIFR |= (0x01<<1); //Clear any pending Interrupt Flag
}
template <> inline void Timer8bit::disableOutputCompareMatchInterrupt<'B'>() const noexcept {
	uint8_t* regTIMSK = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIMSK(this->timerIndex));
	uint8_t* regTIFR = reinterpret_cast<uint8_t*>(AddressMap::getRegisterTIFR(this->timerIndex));
	*regTIMSK &= ~(0x01<<2);
	*regTIFR |= (0x01<<2); //Clear any pending Interrupt Flag
}


#endif /* SRC_RESOURCES_PERIPHERY_TIMER8BIT_H_ */
