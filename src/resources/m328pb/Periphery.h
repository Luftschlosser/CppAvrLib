#ifndef SRC_RESOURCES_M328P_PERIPHERY_H_
#define SRC_RESOURCES_M328P_PERIPHERY_H_


#include <avr/io.h>
#include <stdint.h>
#include "AddressMap.h"

#include "../periphery/Port.h"
#include "../periphery/Usart.h"
#include "../periphery/GeneralPurposeRegister.h"
#include "../periphery/Timer8bit.h"
#include "../periphery/Timer8bitAsync.h"
#include "../periphery/Timer16bit.h"
#include "../periphery/Twi.h"
#include "../periphery/Adc.h"
#include "../periphery/Watchdog.h"
#include "../periphery/McuStatus.h"

#include "../periphery/secondary/InterruptPin.h"
#include "../periphery/secondary/Pin.h"
#include "../periphery/secondary/GeneralPurposeFlag.h"
#include "../periphery/secondary/PinChangeInterrupt.h"


///Periphery declaration for the ATmega328p
namespace Periphery {

	//Memory mapped objects
	static Port& portB = *(reinterpret_cast<Port*>(ADR_PORTB));
	static Port& portC = *(reinterpret_cast<Port*>(ADR_PORTC));
	static Port& portD = *(reinterpret_cast<Port*>(ADR_PORTD));
	static Port& portE = *(reinterpret_cast<Port*>(ADR_PORTE));

	static Usart& usart0 = *(reinterpret_cast<Usart*>(ADR_USART0));
	static Usart& usart1 = *(reinterpret_cast<Usart*>(ADR_USART1));

	static GeneralPurposeRegister& gpior0 = *(reinterpret_cast<GeneralPurposeRegister*>(ADR_GPIOR0));
	static GeneralPurposeRegister& gpior1 = *(reinterpret_cast<GeneralPurposeRegister*>(ADR_GPIOR1));
	static GeneralPurposeRegister& gpior2 = *(reinterpret_cast<GeneralPurposeRegister*>(ADR_GPIOR2));

	static Timer16bit& timer1 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER1));
	static Timer16bit& timer3 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER3));
	static Timer16bit& timer4 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER4)); //Caution, different Register Layout! -> OCR4A is at another Address!

	static Twi& twi0 = *(reinterpret_cast<Twi*>(ADR_TWI0));
	static Twi& twi1 = *(reinterpret_cast<Twi*>(ADR_TWI1));

	static Adc& adc = *(reinterpret_cast<Adc*>(ADR_ADC));
	static Watchdog& watchdog = *(reinterpret_cast<Watchdog*>(ADR_WATCHDOG));

	//Device specific Constants
	static constexpr uint8_t Timer16bitChannelCount = 2;
	static constexpr uint8_t AdcChannelCount = 8;
	static constexpr uint8_t AdcNumberOfMuxOptions = 16;
	static constexpr uint16_t EepromMemorySize = 1024;


	//Access to MMIO Periphery
	template <unsigned char Index> inline Port& getPort() noexcept {
		return *(reinterpret_cast<Port*>(AddressMap::getPortAdress<Index>()));
	}
	template <uint8_t Index> inline Usart& getUsart() noexcept {
		return *(reinterpret_cast<Usart*>(AddressMap::getUsartAdress<Index>()));
	}
	template <uint8_t Index> inline GeneralPurposeRegister& getGeneralPurposeRegister() noexcept {
		return *(reinterpret_cast<GeneralPurposeRegister*>(AddressMap::getGeneralPurposeRegisterAdress<Index>()));
	}
	template <uint8_t Index> inline Timer8bit getTimer8bit() noexcept {
		Timer8bit::Registers& registers = *(reinterpret_cast<Timer8bit::Registers*>(AddressMap::getTimer8bitAdress<Index>()));
		return Timer8bit(registers, Index, (Index == 0 ? 0 : 1));
	}
	inline Timer8bitAsync getTimer8bitAsync() noexcept {
		Timer8bit::Registers& registers = *(reinterpret_cast<Timer8bit::Registers*>(AddressMap::getTimer8bitAdress<2>()));
		return Timer8bitAsync(registers, 2);
	}
	template <uint8_t Index> inline Timer16bit& getTimer16bit() noexcept {
		return *(reinterpret_cast<Timer16bit*>(AddressMap::getTimer16bitAdress<Index>()));
	}
	template <uint8_t Index> inline Twi& getTwi() noexcept {
		return *(reinterpret_cast<Twi*>(AddressMap::getTwiAddress<Index>()));
	}
	inline Adc& getAdc() noexcept {
		return *(reinterpret_cast<Adc*>(AddressMap::getAdcAddress()));
	}
	inline Watchdog& getWatchdog() noexcept {
		return *(reinterpret_cast<Watchdog*>(AddressMap::getWatchdogAddress()));
	}
	inline McuStatus& getMcuStatus() noexcept {
		return *(reinterpret_cast<McuStatus*>(AddressMap::getMcuStatusAddress()));
	}

	//Access to secondary Periphery
	template <unsigned char PortIndex, uint8_t PinIndex> inline Pin getPin() noexcept {
		return Pin(getPort<PortIndex>(), PinIndex);
	}
	template <uint8_t Index> inline InterruptPin getInterruptPin() noexcept {
		return InterruptPin(Periphery::getPort<'D'>(), Index+2, Index);
	}

	template <uint8_t Index> inline PinChangeInterrupt getPinChangeInterrupt() noexcept;
	template <> inline PinChangeInterrupt getPinChangeInterrupt<0>() noexcept {
		return PinChangeInterrupt(0);
	}
	template <> inline PinChangeInterrupt getPinChangeInterrupt<1>() noexcept {
		return PinChangeInterrupt(1);
	}
	template <> inline PinChangeInterrupt getPinChangeInterrupt<2>() noexcept {
		return PinChangeInterrupt(2);
	}

	template <unsigned char RegisterIndex, uint8_t BitIndex> inline GeneralPurposeFlag getGeneralPurposeFlag() noexcept {
		return GeneralPurposeFlag(getGeneralPurposeRegister<RegisterIndex>(), BitIndex);
	}

	//Access Pins for alternate Port functions
	inline Pin getPinChangeInterruptPin(uint8_t pinCangeInterruptIndex, uint8_t pinNumber) noexcept {
		switch (pinCangeInterruptIndex) {
		case 0:
			return Pin(getPort<'B'>(), pinNumber);
		case 1:
			return Pin(getPort<'C'>(), pinNumber);
		default: //2
			return Pin(getPort<'D'>(), pinNumber);
		}
	}
	inline Pin getPinChangeInterruptPin(uint8_t pinChangeInterruptPin) noexcept {
		return getPinChangeInterruptPin(pinChangeInterruptPin/8, pinChangeInterruptPin%8);
	}

	template <char Channel> inline Pin getTimer8bitCompareOutputPin(uint8_t timerIndex) noexcept;
	template <> inline Pin getTimer8bitCompareOutputPin<'A'>(uint8_t timerIndex) noexcept {
		if (timerIndex == 0) {
			return Pin(getPort<'D'>(), 6);
		}
		else { //timerIndex == 2 (only other 8bit Timer on this µC)
			return Pin(getPort<'B'>(), 3);
		}
	}
	template <> inline Pin getTimer8bitCompareOutputPin<'B'>(uint8_t timerIndex) noexcept {
		if (timerIndex == 0) {
			return Pin(getPort<'D'>(), 5);
		}
		else { //timerIndex == 2 (only other 8bit Timer on this µC)
			return Pin(getPort<'D'>(), 3);
		}
	}
	inline Pin getTimer8bitExternalClockPin(uint8_t timerIndex) noexcept {
		if (timerIndex == 0) { //timerIndex == 0 -> This one has a synchronous external clock input. (T0)
			return Pin(getPort<'D'>(), 4);
		}
		else { //timerIndex == 2 (only other 8bit Timer on this µC) -> This one has an asynchronous external clock input. (TOSC1)
			return Pin(getPort<'B'>(), 6);
		}
	}
	inline Pin getTimer8bitAsyncOscillatorPin1() noexcept {
		return Pin(getPort<'B'>(), 6);
	}
	inline Pin getTimer8bitAsyncOscillatorPin2() noexcept {
		return Pin(getPort<'B'>(), 7);
	}

	inline constexpr uint8_t getTimer16bitCompareOutputPinCount() noexcept {
		return Timer16bitChannelCount;
	}
	template <char Channel> inline Pin getTimer16bitCompareOutputPin(uint8_t timerIndex) noexcept;
	template <> inline Pin getTimer16bitCompareOutputPin<'A'>(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 3:
			return Pin(getPort<'D'>(), 0);
		case 4:
			return Pin(getPort<'D'>(), 1);
		default: //1
			return Pin(getPort<'B'>(), 1);
		}
	}
	template <> inline Pin getTimer16bitCompareOutputPin<'B'>(uint8_t timerIndex) noexcept {
		if (timerIndex == 1) {
			return Pin(getPort<'B'>(), 2);
		}
		else { //3 & 4
			return Pin(getPort<'D'>(), 2);
		}
	}
	template <> inline Pin getTimer16bitCompareOutputPin<'C'>(uint8_t timerIndex) noexcept {
		return getTimer16bitCompareOutputPin<'B'>(timerIndex); //Forward non-existing Channel 'C' to 'B'
	}
	inline Pin getTimer16bitExternalClockPin(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 3:
			return Pin(getPort<'E'>(), 3);
		case 4:
			return Pin(getPort<'E'>(), 1);
		default: //1
			return Pin(getPort<'D'>(), 5);
		}
	}
	inline Pin getTimer16bitInputCapturePin(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 3:
			return Pin(getPort<'E'>(), 2);
		case 4:
			return Pin(getPort<'E'>(), 0);
		default: //1
			return Pin(getPort<'B'>(), 0);
		}
	}
	inline Pin getTwiSclPin(uint8_t twiIndex) noexcept {
		if (twiIndex == 1) {
			return Pin(getPort<'E'>(), 1);
		}
		else { //0
			return Pin(getPort<'C'>(), 5);
		}
	}
	inline Pin getTwiSdaPin(uint8_t twiIndex) noexcept {
		if (twiIndex == 1) {
			return Pin(getPort<'E'>(), 0);
		}
		else { //0
			return Pin(getPort<'C'>(), 4);
		}
	}
	inline constexpr uint8_t getAdcChannelCount() noexcept {
		return AdcChannelCount;
	}
	inline constexpr uint8_t getAdcNumberOfMuxOptions() noexcept {
		return AdcNumberOfMuxOptions;
	}
	inline Pin getAdcPin(uint8_t adcIndex) noexcept {
		if (adcIndex <= 5) {
			return Pin(getPort<'C'>(), adcIndex);
		}
		else {
			return Pin(getPort<'E'>(), adcIndex - 4);
		}
	}

	///Get the total number of instances of a periphery type.
	///\return The total number of instances of the template-specified type [0-n]
	template <typename T> inline constexpr uint8_t getCapacity() noexcept;
	template <> inline constexpr uint8_t getCapacity<Port>() noexcept { return 4; }
	template <> inline constexpr uint8_t getCapacity<Usart>() noexcept { return 2; }
	template <> inline constexpr uint8_t getCapacity<GeneralPurposeRegister>() noexcept { return 3; }
	template <> inline constexpr uint8_t getCapacity<Pin>() noexcept { return 8 * getCapacity<Port>(); }
	template <> inline constexpr uint8_t getCapacity<InterruptPin>() noexcept { return 2; }
	template <> inline constexpr uint8_t getCapacity<GeneralPurposeFlag>() noexcept { return 8 * getCapacity<GeneralPurposeRegister>(); }
	template <> inline constexpr uint8_t getCapacity<Timer8bit>() noexcept { return 2; }
	template <> inline constexpr uint8_t getCapacity<Timer16bit>() noexcept { return 3; }
	template <> inline constexpr uint8_t getCapacity<Twi>() noexcept { return 2; }
	template <> inline constexpr uint8_t getCapacity<Adc>() noexcept { return 1; }
}


#endif /* SRC_RESOURCES_M328P_PERIPHERY_H_ */
