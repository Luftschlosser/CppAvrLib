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


//Forward-Declarations
class Port;
class Usart;


///Functions for bidirectional pointer<->index evaluations of the MMIO-Periphery for the ATmega2560
namespace AddressMap {

	///Address -> Index for the template-specified type
	template <typename T> inline constexpr uint8_t pointerToIndex(intptr_t ptr) noexcept;
	template <> inline constexpr uint8_t pointerToIndex<Port>(intptr_t ptr) noexcept
	{
		if (ptr < 0x100) {
			return (ptr - 0x20) / 0x3;
		}
		else {
			return ((ptr - 0x100) / 0x3) + 0x7;
		}
	}
	template <> inline constexpr uint8_t pointerToIndex<Usart>(intptr_t ptr) noexcept
	{
		if (ptr < 0xFF) {
			return (ptr - 0xC0) / 0x08;
		}
		else {
			return 3;
		}
	}

	///Associated-Character -> Address for the template-specified type
	template <typename T> inline constexpr intptr_t indexToPointer(char index);
	template <> inline constexpr intptr_t indexToPointer<Port>(char index) {
		switch(index) {
		case 'A':
			return ADR_PORTA;
		case 'B':
			return ADR_PORTB;
		case 'C':
			return ADR_PORTC;
		case 'D':
			return ADR_PORTD;
		case 'E':
			return ADR_PORTE;
		case 'F':
			return ADR_PORTF;
		case 'G':
			return ADR_PORTG;
		case 'H':
			return ADR_PORTH;
		case 'J':
			return ADR_PORTJ;
		case 'K':
			return ADR_PORTK;
		case 'L':
			return ADR_PORTL;
		default:
			//TODO: throw
			return ADR_PORTA;
		}
	}

	///Index -> Address for the template-specified type
	template <typename T> inline constexpr intptr_t indexToPointer(uint8_t index);
	template <> inline constexpr intptr_t indexToPointer<Port>(uint8_t index) {
		if (index >= 11) {
			//TODO: throw
			index = 10;
		}
		return index >= 7 ? ((index - 7) * 3) + 0x100 : (index * 3) + 0x20;
	}
	template <> inline constexpr intptr_t indexToPointer<Usart>(uint8_t index) {
		if (index > 3) {
			//TODO: throw
			index = 0;
		}
		return index == 3 ? ADR_USART3 : 0xC0 + (index * 0x08);
	}
}

#endif /* SRC_RESOURCES_M2560_ADDRESSMAP_H_ */
