#ifndef SRC_RESOURCES_M328P_INTERRUPTS_H_
#define SRC_RESOURCES_M328P_INTERRUPTS_H_


#include <avr/interrupt.h>
#include "../Configuration.h"
#include "../interrupts/Interrupt.h"


///Interrupt declaration for the ATmega328p
namespace Interrupts {

	///Access the Interrupt object for the external Interrupt with the template-specified index
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getExternalInterrupt() noexcept;
	template <> inline Interrupt getExternalInterrupt<0>() noexcept { return Interrupt::GetInstance<INT0_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<1>() noexcept { return Interrupt::GetInstance<INT1_vect_num>(); }
	///Access the Interrupt Object for the PinChange Interrupt Port with the template-specified index
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getPinChangeInterrupt() noexcept;
	template <> inline Interrupt getPinChangeInterrupt<0>() noexcept { return Interrupt::GetInstance<PCINT0_vect_num>(); }
	template <> inline Interrupt getPinChangeInterrupt<1>() noexcept { return Interrupt::GetInstance<PCINT1_vect_num>(); }
	template <> inline Interrupt getPinChangeInterrupt<2>() noexcept { return Interrupt::GetInstance<PCINT2_vect_num>(); }

	///Access the Usart RX-Interrupt object for the Usart device
	///\return A reference to the Interrupt object
	inline Interrupt getUsartRxInterrupt() noexcept { return Interrupt::GetInstance<USART_RX_vect_num>(); }

	///Access the Usart TX-Interrupt object for the Usart device
	///\return A reference to the Interrupt object
	inline Interrupt getUsartTxInterrupt() noexcept { return Interrupt::GetInstance<USART_TX_vect_num>(); }

	///Access the Usart UDRE-Interrupt object for the Usart device
	///\return A reference to the Interrupt object
	inline Interrupt getUsartUdreInterrupt() noexcept { return Interrupt::GetInstance<USART_UDRE_vect_num>(); }

	///Access the Timer OC-Interrupt object for the template specified Timer device and compare-match channel
	///\return A reference to the Interrupt object
	template <uint8_t Index, char Channel> inline Interrupt getTimerOcInterrupt() noexcept;
	template <> inline Interrupt getTimerOcInterrupt<0, 'A'>() noexcept { return Interrupt::GetInstance<TIMER0_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<0, 'B'>() noexcept { return Interrupt::GetInstance<TIMER0_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<1, 'A'>() noexcept { return Interrupt::GetInstance<TIMER1_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<1, 'B'>() noexcept { return Interrupt::GetInstance<TIMER1_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<2, 'A'>() noexcept { return Interrupt::GetInstance<TIMER2_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<2, 'B'>() noexcept { return Interrupt::GetInstance<TIMER2_COMPB_vect_num>(); }

	///Access the Timer Overflow Interrupt object for the template specified Timer device
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getTimerOvfInterrupt() noexcept;
	template <> inline Interrupt getTimerOvfInterrupt<0>() noexcept { return Interrupt::GetInstance<TIMER0_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<1>() noexcept { return Interrupt::GetInstance<TIMER1_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<2>() noexcept { return Interrupt::GetInstance<TIMER2_OVF_vect_num>(); }

	///Access the Tiimer Input Capture Interrupt object for the template specified Timer device
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getTimerCaptInterrupt() noexcept;
	template <> inline Interrupt getTimerCaptInterrupt<1>() noexcept { return Interrupt::GetInstance<TIMER1_CAPT_vect_num>(); }

	///Access the Twi Interrupt object
	inline Interrupt getTwiInterrupt() noexcept { return Interrupt::GetInstance<TWI_vect_num>(); }
}


#endif /* SRC_RESOURCES_M328P_INTERRUPTS_H_ */
