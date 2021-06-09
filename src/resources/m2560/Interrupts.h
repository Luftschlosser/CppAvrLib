#ifndef SRC_RESOURCES_M2560_INTERRUPTS_H_
#define SRC_RESOURCES_M2560_INTERRUPTS_H_


///Interrupt declaration for the ATmega2560
namespace Interrupts {

	/*
	static Interrupt externalInterrupt0 = Interrupt::GetInstance<INT0_vect_num>();
	static Interrupt externalInterrupt1 = Interrupt::GetInstance<INT1_vect_num>();
	static Interrupt externalInterrupt2 = Interrupt::GetInstance<INT2_vect_num>();
	static Interrupt externalInterrupt3 = Interrupt::GetInstance<INT3_vect_num>();
	static Interrupt externalInterrupt4 = Interrupt::GetInstance<INT4_vect_num>();
	static Interrupt externalInterrupt5 = Interrupt::GetInstance<INT5_vect_num>();
	static Interrupt externalInterrupt6 = Interrupt::GetInstance<INT6_vect_num>();
	static Interrupt externalInterrupt7 = Interrupt::GetInstance<INT7_vect_num>();

	static Interrupt usartRxIrq0 = Interrupt::GetInstance<USART0_RX_vect_num>();
	static Interrupt usartRxIrq1 = Interrupt::GetInstance<USART1_RX_vect_num>();
	static Interrupt usartRxIrq2 = Interrupt::GetInstance<USART2_RX_vect_num>();
	static Interrupt usartRxIrq3 = Interrupt::GetInstance<USART3_RX_vect_num>();

	static Interrupt usartTxIrq0 = Interrupt::GetInstance<USART0_TX_vect_num>();
	static Interrupt usartTxIrq1 = Interrupt::GetInstance<USART1_TX_vect_num>();
	static Interrupt usartTxIrq2 = Interrupt::GetInstance<USART2_TX_vect_num>();
	static Interrupt usartTxIrq3 = Interrupt::GetInstance<USART3_TX_vect_num>();

	static Interrupt usartUdreIrq0 = Interrupt::GetInstance<USART0_UDRE_vect_num>();
	static Interrupt usartUdreIrq1 = Interrupt::GetInstance<USART1_UDRE_vect_num>();
	static Interrupt usartUdreIrq2 = Interrupt::GetInstance<USART2_UDRE_vect_num>();
	static Interrupt usartUdreIrq3 = Interrupt::GetInstance<USART3_UDRE_vect_num>();
	*/


	///Access the Interrupt object for the external Interrupt with the given index
	///\param index the index of the external Interrupt [0-7]
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

	///Access the Usart RX-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getUsartRxInterrupt() noexcept;
	template <> inline Interrupt getUsartRxInterrupt<0>() noexcept { return Interrupt::GetInstance<USART0_RX_vect_num>(); }
	template <> inline Interrupt getUsartRxInterrupt<1>() noexcept { return Interrupt::GetInstance<USART1_RX_vect_num>(); }
	template <> inline Interrupt getUsartRxInterrupt<2>() noexcept { return Interrupt::GetInstance<USART2_RX_vect_num>(); }
	template <> inline Interrupt getUsartRxInterrupt<3>() noexcept { return Interrupt::GetInstance<USART3_RX_vect_num>(); }

	///Access the Usart TX-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getUsartTxInterrupt() noexcept;
	template <> inline Interrupt getUsartTxInterrupt<0>() noexcept { return Interrupt::GetInstance<USART0_TX_vect_num>(); }
	template <> inline Interrupt getUsartTxInterrupt<1>() noexcept { return Interrupt::GetInstance<USART1_TX_vect_num>(); }
	template <> inline Interrupt getUsartTxInterrupt<2>() noexcept { return Interrupt::GetInstance<USART2_TX_vect_num>(); }
	template <> inline Interrupt getUsartTxInterrupt<3>() noexcept { return Interrupt::GetInstance<USART3_TX_vect_num>(); }

	///Access the Usart UDRE-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline Interrupt getUsartUdreInterrupt() noexcept;
	template <> inline Interrupt getUsartUdreInterrupt<0>() noexcept { return Interrupt::GetInstance<USART0_UDRE_vect_num>(); }
	template <> inline Interrupt getUsartUdreInterrupt<1>() noexcept { return Interrupt::GetInstance<USART1_UDRE_vect_num>(); }
	template <> inline Interrupt getUsartUdreInterrupt<2>() noexcept { return Interrupt::GetInstance<USART2_UDRE_vect_num>(); }
	template <> inline Interrupt getUsartUdreInterrupt<3>() noexcept { return Interrupt::GetInstance<USART3_UDRE_vect_num>(); }
}


#endif /* SRC_RESOURCES_M2560_INTERRUPTS_H_ */
