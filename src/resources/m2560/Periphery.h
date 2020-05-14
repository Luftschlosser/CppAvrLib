#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>
#include <stdint.h>
#include "AddressMap.h"


///Periphery declaration for the ATmega2560
namespace Periphery {

	///Flag to enable/disable periphery runtime allocations
	static constexpr bool runtimeAllocationsEnabled = true;


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


	///Get the Index of a given periphery instance.
	///\param periphery A pointer to the periphery instance
	///\return The index of the periphery [0-n]
	template <typename T> inline uint8_t getIdentity(T* periphery) noexcept {
		return AddressMap::pointerToIndex<T>(reinterpret_cast<intptr_t>(periphery));
	}

	///Access a specific periphery instance.
	///\param index The index [0-n] of the periphery to access
	///\return A reference to the periphery instance
	template <typename T> inline T& getInstance(uint8_t index) {
		return *(reinterpret_cast<T*>(AddressMap::indexToPointer<T>(index)));
	}

	///Access a specific periphery instance.
	///\param index The letter [A-Z] associated with the periphery to access
	///\return A reference to the periphery instance
	template <typename T> inline T& getInstance(char letter) {
		return *(reinterpret_cast<T*>(AddressMap::indexToPointer<T>(letter)));
	}

	///Get the total number of instances of a periphery type.
	///\return The total number of instances of the template-specified type [0-n]
	template <typename T> inline constexpr uint8_t getCapacity() noexcept;
	template <> inline constexpr uint8_t getCapacity<Port>() noexcept { return 11; }
	template <> inline constexpr uint8_t getCapacity<Usart>() noexcept { return 4; }
	template <> inline constexpr uint8_t getCapacity<GeneralPurposeRegister>() noexcept { return 3; }
}

#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
