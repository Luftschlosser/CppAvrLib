#ifndef SRC_RESOURCES_PERIPHERY_TIMER8BITASYNC_H_
#define SRC_RESOURCES_PERIPHERY_TIMER8BITASYNC_H_


#include "Timer8bit.h"


//Forward Declarations
namespace Periphery {
	inline Timer8bitAsync getTimer8bitAsync() noexcept;
	inline Pin getTimer8bitAsyncOscillatorPin1() noexcept;
	inline Pin getTimer8bitAsyncOscillatorPin2() noexcept;
}


///Abstraction of the asynchronous 8bit Timer
class Timer8bitAsync : public Timer8bit {
	friend inline Timer8bitAsync Periphery::getTimer8bitAsync() noexcept;

private:

	///Constructor (friend periphery-function to create instance)
	inline constexpr Timer8bitAsync (Registers& registers, uint8_t timerIndex) noexcept :
			Timer8bit(registers, timerIndex, true) {}

public:

	///Pin-Pair to wrap the two oscillator Pins together
	struct OscillatorPins final {
		Pin oscillatorPin1; //TOSC1
		Pin oscillatorPin2; //TOSC2
	};

	///Destructor
	inline ~Timer8bitAsync() noexcept = default;

	///Enable Asynchronous Operation
	inline void enableAsynchronousOperation() const noexcept {
		this->registers.regASSR.fields.flagAS = 1;
	}

	///Disable Asynchronous Operation
	inline void disableAsynchronousOperation() const noexcept {
		this->registers.regASSR.fields.flagAS = 0;
	}

	///Enables external (asynchronous) clock input
	inline void enableExternalClockInput() const noexcept {
		this->registers.regASSR.fields.flagEXCLK = 1;
	}

	///Disables external (asynchronous) clock input
	inline void disableExternalClockInput() const noexcept {
		this->registers.regASSR.fields.flagEXCLK = 0;
	}

	///Checks if the Timer Counter register is currently busy updating
	inline bool isCounterRegisterUpdateBusy() const noexcept {
		return this->registers.regASSR.fields.flagTCNUB;
	}

	///Checks if the OutputCompareRegister for the template specified output channel is currently busy updating
	template<char Channel> inline bool isOutputCompareRegisterUpdateBusy() const noexcept;

	///Checks if the Timer Counter Control register A (Compare Output- and Waveform Generation Control) is currently busy updating
	inline bool isCounterControlRegisterAUpdateBusy() const noexcept {
		return this->registers.regASSR.fields.flagTCRAUB;
	}

	///Checks if the Timer Counter Control register B (Waveform Generation-, Force Output Compare- and Clock Select Control) is currently busy updating
	inline bool isCounterControlRegisterBUpdateBusy() const noexcept {
		return this->registers.regASSR.fields.flagTCRBUB;
	}

	///Checks if any Timer register is busy updating
	inline bool isAnyRegisterUpdateBusy() const noexcept {
		return (this->registers.regASSR.reg & 0x1F); //Mask = 0b00011111
	}

	///get the two oscillator Pins to connect a crystal oscillator for asynchronous timer control
	inline OscillatorPins getOscillatorPins() const noexcept {
		OscillatorPins pins = {Periphery::getTimer8bitAsyncOscillatorPin1(), Periphery::getTimer8bitAsyncOscillatorPin2()};
		return pins;
	}
};


//Implementations of Member-Specializations
template <> inline bool Timer8bitAsync::isOutputCompareRegisterUpdateBusy<'A'>() const noexcept {
	return this->registers.regASSR.fields.flagOCRAUB;
}
template <> inline bool Timer8bitAsync::isOutputCompareRegisterUpdateBusy<'B'>() const noexcept {
	return this->registers.regASSR.fields.flagOCRBUB;
}


#endif /* SRC_RESOURCES_PERIPHERY_TIMER8BITASYNC_H_ */
