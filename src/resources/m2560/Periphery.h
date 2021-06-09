#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>
#include <stdint.h>
#include "AddressMap.h"

#include "../periphery/Port.h"
#include "../periphery/Usart.h"
#include "../periphery/GeneralPurposeRegister.h"

#include "../periphery/secondary/InterruptPin.h"
#include "../periphery/secondary/Pin.h"
#include "../periphery/secondary/GeneralPurposeFlag.h"


///Periphery declaration for the ATmega2560
namespace Periphery {

	/*
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
	*/

	///Access a specific periphery instance.
	///\param index The index ['0-n' or 'A-Z' for Ports] of the periphery to access
	///\return A reference to the periphery instance
	template <typename T, unsigned char Index> inline T& getInstance() noexcept {
		return *(reinterpret_cast<T*>(AddressMap::getAdress<T, Index>()));
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 0>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 0, 0);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 1>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 1, 1);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 2>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 2, 2);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 3>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 3, 3);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 4>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 4, 4);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 5>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 5, 5);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 6>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 6, 6);
		return iPin;
	}
	template <> inline InterruptPin& getInstance<InterruptPin, 7>() noexcept {
		static InterruptPin iPin = InterruptPin(Periphery::getInstance<Port, 'B'>(), 7, 7);
		return iPin;
	}

	///Get the total number of instances of a periphery type.
	///\return The total number of instances of the template-specified type [0-n]
	template <typename T> inline constexpr uint8_t getCapacity() noexcept;
	template <> inline constexpr uint8_t getCapacity<Port>() noexcept { return 11; }
	template <> inline constexpr uint8_t getCapacity<Usart>() noexcept { return 4; }
	template <> inline constexpr uint8_t getCapacity<GeneralPurposeRegister>() noexcept { return 3; }
	template <> inline constexpr uint8_t getCapacity<InterruptPin>() noexcept { return 8; }
}

#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
