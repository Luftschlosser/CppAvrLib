#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>
#include <stdint.h>
#include "AddressMap.h"

#include "../periphery/Port.h"
#include "../periphery/Usart.h"
#include "../periphery/GeneralPurposeRegister.h"
#include "../periphery/Timer8bit.h"

#include "../periphery/secondary/InterruptPin.h"
#include "../periphery/secondary/Pin.h"
#include "../periphery/secondary/GeneralPurposeFlag.h"


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
	template <unsigned char RegisterIndex, uint8_t BitIndex> inline GeneralPurposeFlag getGeneralPurposeFlag() noexcept {
		return GeneralPurposeFlag(getGeneralPurposeRegister<RegisterIndex>(), BitIndex);
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
}

#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
