#ifndef SRC_RESOURCES_M328P_ADDRESSMAP_H_
#define SRC_RESOURCES_M328P_ADDRESSMAP_H_


#include <stdint.h>


//Redefinition of MMIO-Periphery addresses (needed because <avr/io.h> contains casts, which can't be used in constexpr functions)
#define ADR_PORTB 0x23
#define ADR_PORTC 0x26
#define ADR_PORTD 0x29

#define ADR_USART 0xC0

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
#define ADR_TIFR 0x35
#define ADR_TIMSK 0x6E
#define ADR_GTCCR 0x43

#define ADR_TWI 0xB8
#define ADR_ADC 0x78
#define ADR_WATCHDOG 0x60
#define ADR_MCU_STATUS 0x54

//Forward-Declarations
class Port;
class Usart;
class GeneralPurposeRegister;
class Timer16bit;
class Twi;
class Adc;

///Functions for bidirectional pointer<->index evaluations of the MMIO-Periphery for the ATmega328p
namespace AddressMap {

	///Get the Index of a given periphery instance.
	///\param periphery A pointer to the periphery instance
	///\return The index of the periphery [0-n]
	inline uint8_t getIdentity(const Port* periphery) noexcept {
		const intptr_t ptr = reinterpret_cast<intptr_t>(periphery);
		return (ptr - 0x20) / 0x3;
	}
	inline uint8_t getIdentity(const Usart* periphery) noexcept {
		return 0;
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
		return 1;
	}
	inline constexpr uint8_t getIdentity(const Twi* periphery) noexcept {
		return 0; //Only 1 exists
	}
	inline constexpr uint8_t getIdentity(const Adc* periphery) noexcept {
		return 0; //Only 1 exists
	}

	///index -> Address for the template-specified type
	template <unsigned char Index> inline constexpr intptr_t getPortAdress() noexcept;
	template <> inline constexpr intptr_t getPortAdress<'B'>() noexcept { return ADR_PORTB; }
	template <> inline constexpr intptr_t getPortAdress<'C'>() noexcept { return ADR_PORTC; }
	template <> inline constexpr intptr_t getPortAdress<'D'>() noexcept { return ADR_PORTD; }

	template <uint8_t Index> inline constexpr intptr_t getGeneralPurposeRegisterAdress() noexcept;
	template <> inline constexpr intptr_t getGeneralPurposeRegisterAdress<0>() noexcept { return ADR_GPIOR0; }
	template <> inline constexpr intptr_t getGeneralPurposeRegisterAdress<1>() noexcept { return ADR_GPIOR1; }
	template <> inline constexpr intptr_t getGeneralPurposeRegisterAdress<2>() noexcept { return ADR_GPIOR2; }

	template <uint8_t Index> inline constexpr intptr_t getTimer8bitAdress() noexcept;
	template <> inline constexpr intptr_t getTimer8bitAdress<0>() noexcept { return ADR_TIMER0; }
	template <> inline constexpr intptr_t getTimer8bitAdress<2>() noexcept { return ADR_TIMER2; }

	inline constexpr intptr_t getTimer16bitAdress() noexcept { return ADR_TIMER1; }

	inline constexpr intptr_t getTwiAddress() noexcept { return ADR_TWI; }
	inline constexpr intptr_t getAdcAddress() noexcept { return ADR_ADC; }
	inline constexpr intptr_t getWatchdogAddress() noexcept { return ADR_WATCHDOG; }
	inline constexpr intptr_t getMcuStatusAddress() noexcept { return ADR_MCU_STATUS; }

	inline constexpr intptr_t getRegisterTIFR(uint8_t index) noexcept { return ADR_TIFR + index; }
	inline constexpr intptr_t getRegisterTIMSK(uint8_t index) noexcept { return ADR_TIMSK + index; }

	inline constexpr intptr_t getRegisterPCMSK(uint8_t index) noexcept { return ADR_PCMSK0 + index; }
}


#endif /* SRC_RESOURCES_M328P_ADDRESSMAP_H_ */
