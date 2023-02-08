#ifndef SRC_RESOURCES_M2560_INTERRUPTS_H_
#define SRC_RESOURCES_M2560_INTERRUPTS_H_


///Interrupt declaration for the ATmega2560
namespace Interrupts {

	///Access the Interrupt object for the external Interrupt with the template-specified index
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getExternalInterrupt() noexcept;
	template <> inline Interrupt getExternalInterrupt<0>() noexcept { return Interrupt::GetInstance<INT0_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<1>() noexcept { return Interrupt::GetInstance<INT1_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<2>() noexcept { return Interrupt::GetInstance<INT2_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<3>() noexcept { return Interrupt::GetInstance<INT3_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<4>() noexcept { return Interrupt::GetInstance<INT4_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<5>() noexcept { return Interrupt::GetInstance<INT5_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<6>() noexcept { return Interrupt::GetInstance<INT6_vect_num>(); }
	template <> inline Interrupt getExternalInterrupt<7>() noexcept { return Interrupt::GetInstance<INT7_vect_num>(); }

	///Access the Usart RX-Interrupt object for the Usart device with the template-specified index
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getUsartRxInterrupt() noexcept;
	template <> inline Interrupt getUsartRxInterrupt<0>() noexcept { return Interrupt::GetInstance<USART0_RX_vect_num>(); }
	template <> inline Interrupt getUsartRxInterrupt<1>() noexcept { return Interrupt::GetInstance<USART1_RX_vect_num>(); }
	template <> inline Interrupt getUsartRxInterrupt<2>() noexcept { return Interrupt::GetInstance<USART2_RX_vect_num>(); }
	template <> inline Interrupt getUsartRxInterrupt<3>() noexcept { return Interrupt::GetInstance<USART3_RX_vect_num>(); }

	///Access the Usart TX-Interrupt object for the Usart device with the template-specified index
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getUsartTxInterrupt() noexcept;
	template <> inline Interrupt getUsartTxInterrupt<0>() noexcept { return Interrupt::GetInstance<USART0_TX_vect_num>(); }
	template <> inline Interrupt getUsartTxInterrupt<1>() noexcept { return Interrupt::GetInstance<USART1_TX_vect_num>(); }
	template <> inline Interrupt getUsartTxInterrupt<2>() noexcept { return Interrupt::GetInstance<USART2_TX_vect_num>(); }
	template <> inline Interrupt getUsartTxInterrupt<3>() noexcept { return Interrupt::GetInstance<USART3_TX_vect_num>(); }

	///Access the Usart UDRE-Interrupt object for the Usart device with the template-specified index
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getUsartUdreInterrupt() noexcept;
	template <> inline Interrupt getUsartUdreInterrupt<0>() noexcept { return Interrupt::GetInstance<USART0_UDRE_vect_num>(); }
	template <> inline Interrupt getUsartUdreInterrupt<1>() noexcept { return Interrupt::GetInstance<USART1_UDRE_vect_num>(); }
	template <> inline Interrupt getUsartUdreInterrupt<2>() noexcept { return Interrupt::GetInstance<USART2_UDRE_vect_num>(); }
	template <> inline Interrupt getUsartUdreInterrupt<3>() noexcept { return Interrupt::GetInstance<USART3_UDRE_vect_num>(); }

	///Access the Timer OC-Interrupt object for the template specified Timer device and compare-match channel
	///\return A reference to the Interrupt object
	template <uint8_t Index, char Channel> inline Interrupt getTimerOcInterrupt() noexcept;
	template <> inline Interrupt getTimerOcInterrupt<0, 'A'>() noexcept { return Interrupt::GetInstance<TIMER0_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<0, 'B'>() noexcept { return Interrupt::GetInstance<TIMER0_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<1, 'A'>() noexcept { return Interrupt::GetInstance<TIMER1_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<1, 'B'>() noexcept { return Interrupt::GetInstance<TIMER1_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<1, 'C'>() noexcept { return Interrupt::GetInstance<TIMER1_COMPC_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<2, 'A'>() noexcept { return Interrupt::GetInstance<TIMER2_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<2, 'B'>() noexcept { return Interrupt::GetInstance<TIMER2_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<3, 'A'>() noexcept { return Interrupt::GetInstance<TIMER3_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<3, 'B'>() noexcept { return Interrupt::GetInstance<TIMER3_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<3, 'C'>() noexcept { return Interrupt::GetInstance<TIMER3_COMPC_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<4, 'A'>() noexcept { return Interrupt::GetInstance<TIMER4_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<4, 'B'>() noexcept { return Interrupt::GetInstance<TIMER4_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<4, 'C'>() noexcept { return Interrupt::GetInstance<TIMER4_COMPC_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<5, 'A'>() noexcept { return Interrupt::GetInstance<TIMER5_COMPA_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<5, 'B'>() noexcept { return Interrupt::GetInstance<TIMER5_COMPB_vect_num>(); }
	template <> inline Interrupt getTimerOcInterrupt<5, 'C'>() noexcept { return Interrupt::GetInstance<TIMER5_COMPC_vect_num>(); }

	///Access the Timer Overflow Interrupt object for the template specified Timer device
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getTimerOvfInterrupt() noexcept;
	template <> inline Interrupt getTimerOvfInterrupt<0>() noexcept { return Interrupt::GetInstance<TIMER0_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<1>() noexcept { return Interrupt::GetInstance<TIMER1_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<2>() noexcept { return Interrupt::GetInstance<TIMER2_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<3>() noexcept { return Interrupt::GetInstance<TIMER3_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<4>() noexcept { return Interrupt::GetInstance<TIMER4_OVF_vect_num>(); }
	template <> inline Interrupt getTimerOvfInterrupt<5>() noexcept { return Interrupt::GetInstance<TIMER5_OVF_vect_num>(); }

	///Access the Tiimer Input Capture Interrupt object for the template specified Timer device
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getTimerCaptInterrupt() noexcept;
	template <> inline Interrupt getTimerCaptInterrupt<1>() noexcept { return Interrupt::GetInstance<TIMER1_CAPT_vect_num>(); }
	template <> inline Interrupt getTimerCaptInterrupt<3>() noexcept { return Interrupt::GetInstance<TIMER3_CAPT_vect_num>(); }
	template <> inline Interrupt getTimerCaptInterrupt<4>() noexcept { return Interrupt::GetInstance<TIMER4_CAPT_vect_num>(); }
	template <> inline Interrupt getTimerCaptInterrupt<5>() noexcept { return Interrupt::GetInstance<TIMER5_CAPT_vect_num>(); }
}


#endif /* SRC_RESOURCES_M2560_INTERRUPTS_H_ */
