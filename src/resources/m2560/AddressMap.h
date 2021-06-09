#ifndef SRC_RESOURCES_M2560_ADDRESSMAP_H_
#define SRC_RESOURCES_M2560_ADDRESSMAP_H_


#include <stdint.h>


//Redefinition of MMIO-Periphery addresses (needed because <avr/io.h> contains casts, which can't be used in constexpr functions)
#define ADR_PORTA 0x20
#define ADR_PORTB 0x23
#define ADR_PORTC 0x26
#define ADR_PORTD 0x29
#define ADR_PORTE 0x2C
#define ADR_PORTF 0x2F
#define ADR_PORTG 0x32
#define ADR_PORTH 0x100
#define ADR_PORTJ 0x103
#define ADR_PORTK 0x106
#define ADR_PORTL 0x109

#define ADR_USART0 0xC0
#define ADR_USART1 0xC8
#define ADR_USART2 0xD0
#define ADR_USART3 0x130

#define ADR_GPIOR0 0x3E
#define ADR_GPIOR1 0x4A
#define ADR_GPIOR2 0x4B

#define ADR_EICRA 0x69
#define ADR_EIFR 0x3C
#define ADR_EIMSK 0x3D


//Forward-Declarations
class Port;
class Usart;
class GeneralPurposeRegister;


///Functions for bidirectional pointer<->index evaluations of the MMIO-Periphery for the ATmega2560
namespace AddressMap {

	///Get the Index of a given periphery instance.
	///\param periphery A pointer to the periphery instance
	///\return The index of the periphery [0-n]
	inline uint8_t getIdentity(const Port* periphery) noexcept {
		const intptr_t ptr = reinterpret_cast<intptr_t>(periphery);
		if (ptr < 0x100) {
			return (ptr - 0x20) / 0x3;
		}
		else {
			return ((ptr - 0x100) / 0x3) + 0x7;
		}
	}
	inline uint8_t getIdentity(const Usart* periphery) noexcept {
		const intptr_t ptr = reinterpret_cast<intptr_t>(periphery);
		if (ptr < 0xFF) {
			return (ptr - 0xC0) / 0x08;
		}
		else {
			return 3;
		}
	}
	inline uint8_t getIdentity(const GeneralPurposeRegister* periphery) noexcept {
		const intptr_t ptr = reinterpret_cast<intptr_t>(periphery);
		if (ptr == 0x3E) {
			return 0;
		}
		else { // 1,2
			return ptr - 0x49;
		}
	}

	///index -> Address for the template-specified type
	template <typename T, unsigned char Index> inline constexpr intptr_t getAdress() noexcept;

	template <> inline constexpr intptr_t getAdress<Port, 'A'>() noexcept { return ADR_PORTA; }
	template <> inline constexpr intptr_t getAdress<Port, 'B'>() noexcept { return ADR_PORTB; }
	template <> inline constexpr intptr_t getAdress<Port, 'C'>() noexcept { return ADR_PORTC; }
	template <> inline constexpr intptr_t getAdress<Port, 'D'>() noexcept { return ADR_PORTD; }
	template <> inline constexpr intptr_t getAdress<Port, 'E'>() noexcept { return ADR_PORTE; }
	template <> inline constexpr intptr_t getAdress<Port, 'F'>() noexcept { return ADR_PORTF; }
	template <> inline constexpr intptr_t getAdress<Port, 'G'>() noexcept { return ADR_PORTG; }
	template <> inline constexpr intptr_t getAdress<Port, 'H'>() noexcept { return ADR_PORTH; }
	template <> inline constexpr intptr_t getAdress<Port, 'J'>() noexcept { return ADR_PORTJ; }
	template <> inline constexpr intptr_t getAdress<Port, 'K'>() noexcept { return ADR_PORTK; }
	template <> inline constexpr intptr_t getAdress<Port, 'L'>() noexcept { return ADR_PORTL; }

	template <> inline constexpr intptr_t getAdress<Usart, 0>() noexcept { return ADR_USART0; }
	template <> inline constexpr intptr_t getAdress<Usart, 1>() noexcept { return ADR_USART1; }
	template <> inline constexpr intptr_t getAdress<Usart, 2>() noexcept { return ADR_USART2; }
	template <> inline constexpr intptr_t getAdress<Usart, 3>() noexcept { return ADR_USART3; }

	template <> inline constexpr intptr_t getAdress<GeneralPurposeRegister, 0>() noexcept { return ADR_GPIOR0; }
	template <> inline constexpr intptr_t getAdress<GeneralPurposeRegister, 1>() noexcept { return ADR_GPIOR1; }
	template <> inline constexpr intptr_t getAdress<GeneralPurposeRegister, 2>() noexcept { return ADR_GPIOR2; }
}

#endif /* SRC_RESOURCES_M2560_ADDRESSMAP_H_ */
