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

#define ADR_PCICR 0x68
#define ADR_PCIFR 0x3B
#define ADR_PCMSK0 0x6B
#define ADR_PCMSK1 0x6C
#define ADR_PCMSK2 0x6D

#define ADR_TIMER0 0x44
#define ADR_TIMER1 0x80
#define ADR_TIMER2 0xB0
#define ADR_TIMER3 0x90
#define ADR_TIMER4 0xA0
#define ADR_TIMER5 0x120
#define ADR_TIFR 0x35
#define ADR_TIMSK 0x6E
#define ADR_GTCCR 0x43

#define ADR_TWI 0xB8
#define ADR_ADC 0x78
#define ADR_WATCHDOG 0x60

//Forward-Declarations
class Port;
class Usart;
class GeneralPurposeRegister;
class Timer16bit;
class Twi;
class Adc;

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
	inline uint8_t getIdentity(const Timer16bit* periphery) noexcept {
		const intptr_t ptr = reinterpret_cast<intptr_t>(periphery);
		if (ptr == 0x120) { //5
			return 5;
		}
		else { //1,3,4
			uint8_t returnBuf = (ptr/0x10)-0x06;
			if (returnBuf == 2) {
				returnBuf--;
			}
			return returnBuf;
		}
	}
	inline constexpr uint8_t getIdentity(const Twi* periphery) noexcept {
		return 0; //Only 1 exists
	}
	inline constexpr uint8_t getIdentity(const Adc* periphery) noexcept {
		return 0; //Only 1 exists
	}

	///index -> Address for the template-specified type
	template <unsigned char Index> inline constexpr intptr_t getPortAdress() noexcept;
	template <> inline constexpr intptr_t getPortAdress<'A'>() noexcept { return ADR_PORTA; }
	template <> inline constexpr intptr_t getPortAdress<'B'>() noexcept { return ADR_PORTB; }
	template <> inline constexpr intptr_t getPortAdress<'C'>() noexcept { return ADR_PORTC; }
	template <> inline constexpr intptr_t getPortAdress<'D'>() noexcept { return ADR_PORTD; }
	template <> inline constexpr intptr_t getPortAdress<'E'>() noexcept { return ADR_PORTE; }
	template <> inline constexpr intptr_t getPortAdress<'F'>() noexcept { return ADR_PORTF; }
	template <> inline constexpr intptr_t getPortAdress<'G'>() noexcept { return ADR_PORTG; }
	template <> inline constexpr intptr_t getPortAdress<'H'>() noexcept { return ADR_PORTH; }
	template <> inline constexpr intptr_t getPortAdress<'J'>() noexcept { return ADR_PORTJ; }
	template <> inline constexpr intptr_t getPortAdress<'K'>() noexcept { return ADR_PORTK; }
	template <> inline constexpr intptr_t getPortAdress<'L'>() noexcept { return ADR_PORTL; }

	template <uint8_t Index> inline constexpr intptr_t getUsartAdress() noexcept;
	template <> inline constexpr intptr_t getUsartAdress<0>() noexcept { return ADR_USART0; }
	template <> inline constexpr intptr_t getUsartAdress<1>() noexcept { return ADR_USART1; }
	template <> inline constexpr intptr_t getUsartAdress<2>() noexcept { return ADR_USART2; }
	template <> inline constexpr intptr_t getUsartAdress<3>() noexcept { return ADR_USART3; }

	template <uint8_t Index> inline constexpr intptr_t getGeneralPurposeRegisterAdress() noexcept;
	template <> inline constexpr intptr_t getGeneralPurposeRegisterAdress<0>() noexcept { return ADR_GPIOR0; }
	template <> inline constexpr intptr_t getGeneralPurposeRegisterAdress<1>() noexcept { return ADR_GPIOR1; }
	template <> inline constexpr intptr_t getGeneralPurposeRegisterAdress<2>() noexcept { return ADR_GPIOR2; }

	template <uint8_t Index> inline constexpr intptr_t getTimer8bitAdress() noexcept;
	template <> inline constexpr intptr_t getTimer8bitAdress<0>() noexcept { return ADR_TIMER0; }
	template <> inline constexpr intptr_t getTimer8bitAdress<2>() noexcept { return ADR_TIMER2; }

	template <uint8_t Index> inline constexpr intptr_t getTimer16bitAdress() noexcept;
	template <> inline constexpr intptr_t getTimer16bitAdress<1>() noexcept { return ADR_TIMER1; }
	template <> inline constexpr intptr_t getTimer16bitAdress<3>() noexcept { return ADR_TIMER3; }
	template <> inline constexpr intptr_t getTimer16bitAdress<4>() noexcept { return ADR_TIMER4; }
	template <> inline constexpr intptr_t getTimer16bitAdress<5>() noexcept { return ADR_TIMER5; }

	inline constexpr intptr_t getTwiAddress() noexcept { return ADR_TWI; }
	inline constexpr intptr_t getAdcAddress() noexcept { return ADR_ADC; }
	inline constexpr intptr_t getWatchdogAddress() noexcept { return ADR_WATCHDOG; }

	inline constexpr intptr_t getRegisterTIFR(uint8_t index) noexcept { return ADR_TIFR + index; }
	inline constexpr intptr_t getRegisterTIMSK(uint8_t index) noexcept { return ADR_TIMSK + index; }

	inline constexpr intptr_t getRegisterPCMSK(uint8_t index) noexcept { return ADR_PCMSK0 + index; }
}

#endif /* SRC_RESOURCES_M2560_ADDRESSMAP_H_ */
