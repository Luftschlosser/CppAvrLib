#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>
#include <stdint.h>
#include "AddressMap.h"

#include "../periphery/Port.h"
#include "../periphery/Usart.h"
#include "../periphery/GeneralPurposeRegister.h"
#include "../periphery/Timer8bit.h"
#include "../periphery/Timer8bitAsync.h"
#include "../periphery/Timer16bit.h"

#include "../periphery/secondary/InterruptPin.h"
#include "../periphery/secondary/Pin.h"
#include "../periphery/secondary/GeneralPurposeFlag.h"
#include "../periphery/secondary/PinChangeInterrupt.h"


///Periphery declaration for the ATmega2560
namespace Periphery {

	//Memory mapped objects
	static Port& portA = *(reinterpret_cast<Port*>(ADR_PORTA));
	static Port& portB = *(reinterpret_cast<Port*>(ADR_PORTB));
	static Port& portC = *(reinterpret_cast<Port*>(ADR_PORTC));
	static Port& portD = *(reinterpret_cast<Port*>(ADR_PORTD));
	static Port& portE = *(reinterpret_cast<Port*>(ADR_PORTE));
	static Port& portF = *(reinterpret_cast<Port*>(ADR_PORTF));
	static Port& portG = *(reinterpret_cast<Port*>(ADR_PORTG));
	static Port& portH = *(reinterpret_cast<Port*>(ADR_PORTH));
	static Port& portJ = *(reinterpret_cast<Port*>(ADR_PORTJ));
	static Port& portK = *(reinterpret_cast<Port*>(ADR_PORTK));
	static Port& portL = *(reinterpret_cast<Port*>(ADR_PORTL));

	static Usart& usart0 = *(reinterpret_cast<Usart*>(ADR_USART0));
	static Usart& usart1 = *(reinterpret_cast<Usart*>(ADR_USART1));
	static Usart& usart2 = *(reinterpret_cast<Usart*>(ADR_USART2));
	static Usart& usart3 = *(reinterpret_cast<Usart*>(ADR_USART3));

	static GeneralPurposeRegister& gpior0 = *(reinterpret_cast<GeneralPurposeRegister*>(ADR_GPIOR0));
	static GeneralPurposeRegister& gpior1 = *(reinterpret_cast<GeneralPurposeRegister*>(ADR_GPIOR1));
	static GeneralPurposeRegister& gpior2 = *(reinterpret_cast<GeneralPurposeRegister*>(ADR_GPIOR2));

	static Timer16bit& timer1 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER1));
	static Timer16bit& timer3 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER3));
	static Timer16bit& timer4 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER4));
	static Timer16bit& timer5 = *(reinterpret_cast<Timer16bit*>(ADR_TIMER5));


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

	//Access to secondary Periphery
	template <unsigned char PortIndex, uint8_t PinIndex> inline Pin getPin() noexcept {
		return Pin(getPort<PortIndex>(), PinIndex);
	}
	template <uint8_t Index> inline InterruptPin getInterruptPin() noexcept {
		if (Index < 4) {
			return InterruptPin(Periphery::getPort<'D'>(), Index, Index);
		}
		else {
			return InterruptPin(Periphery::getPort<'E'>(), Index, Index);
		}
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
			if (pinNumber == 0) {
				return Pin(getPort<'E'>(), 0);
			}
			else {
				return Pin(getPort<'J'>(), pinNumber-1);
			}
		default: //2
			return Pin(getPort<'K'>(), pinNumber);
		}
	}
	inline Pin getPinChangeInterruptPin(uint8_t pinChangeInterruptPin) noexcept {
		return getPinChangeInterruptPin(pinChangeInterruptPin/8, pinChangeInterruptPin%8);
	}

	template <char Channel> inline Pin getTimer8bitCompareOutputPin(uint8_t timerIndex) noexcept;
	template <> inline Pin getTimer8bitCompareOutputPin<'A'>(uint8_t timerIndex) noexcept {
		if (timerIndex == 0) {
			return Pin(getPort<'B'>(), 7);
		}
		else { //timerIndex == 2 (only other 8bit Timer on this µC)
			return Pin(getPort<'B'>(), 4);
		}
	}
	template <> inline Pin getTimer8bitCompareOutputPin<'B'>(uint8_t timerIndex) noexcept {
		if (timerIndex == 0) {
			return Pin(getPort<'G'>(), 5);
		}
		else { //timerIndex == 2 (only other 8bit Timer on this µC)
			return Pin(getPort<'H'>(), 6);
		}
	}
	inline Pin getTimer8bitExternalClockPin(uint8_t timerIndex) noexcept {
		if (timerIndex == 0) { //timerIndex == 0 -> This one has a synchronous external clock input. (T0)
			return Pin(getPort<'D'>(), 7);
		}
		else { //timerIndex == 2 (only other 8bit Timer on this µC) -> This one has an asynchronous external clock input. (TOSC1)
			return Pin(getPort<'G'>(), 4);
		}
	}
	inline Pin getTimer8bitAsyncOscillatorPin1() noexcept {
		return Pin(getPort<'G'>(), 4);
	}
	inline Pin getTimer8bitAsyncOscillatorPin2() noexcept {
		return Pin(getPort<'G'>(), 3);
	}
	inline constexpr uint8_t getTimer16bitCompareOutputPinCount() noexcept {
		return 3;
	}
	template <char Channel> inline Pin getTimer16bitCompareOutputPin(uint8_t timerIndex) noexcept;
	template <> inline Pin getTimer16bitCompareOutputPin<'A'>(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 1:
			return Pin(getPort<'B'>(), 5);
		case 3:
			return Pin(getPort<'E'>(), 3);
		case 4:
			return Pin(getPort<'H'>(), 3);
		default: //5
			return Pin(getPort<'L'>(), 3);
		}
	}
	template <> inline Pin getTimer16bitCompareOutputPin<'B'>(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 1:
			return Pin(getPort<'B'>(), 6);
		case 3:
			return Pin(getPort<'E'>(), 4);
		case 4:
			return Pin(getPort<'H'>(), 4);
		default: //5
			return Pin(getPort<'L'>(), 4);
		}
	}
	template <> inline Pin getTimer16bitCompareOutputPin<'C'>(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 1:
			return Pin(getPort<'B'>(), 7);
		case 3:
			return Pin(getPort<'E'>(), 5);
		case 4:
			return Pin(getPort<'H'>(), 5);
		default: //5
			return Pin(getPort<'L'>(), 5);
		}
	}
	inline Pin getTimer16bitExternalClockPin(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 1:
			return Pin(getPort<'D'>(), 6);
		case 3:
			return Pin(getPort<'E'>(), 6);
		case 4:
			return Pin(getPort<'H'>(), 7);
		default: //5
			return Pin(getPort<'L'>(), 2);
		}
	}
	inline Pin getTimer16bitInputCapturePin(uint8_t timerIndex) noexcept {
		switch (timerIndex) {
		case 1:
			return Pin(getPort<'D'>(), 4);
		case 3:
			return Pin(getPort<'E'>(), 7);
		case 4:
			return Pin(getPort<'L'>(), 0);
		default: //5
			return Pin(getPort<'L'>(), 1);
		}
	}

	///Get the total number of instances of a periphery type.
	///\return The total number of instances of the template-specified type [0-n]
	template <typename T> inline constexpr uint8_t getCapacity() noexcept;
	template <> inline constexpr uint8_t getCapacity<Port>() noexcept { return 11; }
	template <> inline constexpr uint8_t getCapacity<Usart>() noexcept { return 4; }
	template <> inline constexpr uint8_t getCapacity<GeneralPurposeRegister>() noexcept { return 3; }
	template <> inline constexpr uint8_t getCapacity<Pin>() noexcept { return 8 * getCapacity<Port>(); }
	template <> inline constexpr uint8_t getCapacity<InterruptPin>() noexcept { return 8; }
	template <> inline constexpr uint8_t getCapacity<GeneralPurposeFlag>() noexcept { return 8 * getCapacity<GeneralPurposeRegister>(); }
	template <> inline constexpr uint8_t getCapacity<Timer8bit>() noexcept { return 2; }
	template <> inline constexpr uint8_t getCapacity<Timer16bit>() noexcept { return 4; }
}

#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
