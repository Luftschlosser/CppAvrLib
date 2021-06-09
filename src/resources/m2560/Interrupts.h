#ifndef SRC_RESOURCES_M2560_INTERRUPTS_H_
#define SRC_RESOURCES_M2560_INTERRUPTS_H_


///Interrupt declaration for the ATmega2560
namespace Interrupts {

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


	///Access the Interrupt object for the external Interrupt with the given index
	///\param index the index of the external Interrupt [0-7]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline constexpr Interrupt& accessExternalInterrupt() noexcept;
	template <> inline constexpr Interrupt& accessExternalInterrupt<0>() noexcept { return externalInterrupt0; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<1>() noexcept { return externalInterrupt1; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<2>() noexcept { return externalInterrupt2; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<3>() noexcept { return externalInterrupt3; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<4>() noexcept { return externalInterrupt4; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<5>() noexcept { return externalInterrupt5; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<6>() noexcept { return externalInterrupt6; }
	template <> inline constexpr Interrupt& accessExternalInterrupt<7>() noexcept { return externalInterrupt7; }

	///Access the Usart RX-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline constexpr Interrupt& accessUsartRxInterrupt() noexcept;
	template <> inline constexpr Interrupt& accessUsartRxInterrupt<0>() noexcept { return usartRxIrq0; }
	template <> inline constexpr Interrupt& accessUsartRxInterrupt<1>() noexcept { return usartRxIrq1; }
	template <> inline constexpr Interrupt& accessUsartRxInterrupt<2>() noexcept { return usartRxIrq2; }
	template <> inline constexpr Interrupt& accessUsartRxInterrupt<3>() noexcept { return usartRxIrq3; }

	///Access the Usart TX-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline constexpr Interrupt& accessUsartTxInterrupt() noexcept;
	template <> inline constexpr Interrupt& accessUsartTxInterrupt<0>() noexcept { return usartTxIrq0; }
	template <> inline constexpr Interrupt& accessUsartTxInterrupt<1>() noexcept { return usartTxIrq1; }
	template <> inline constexpr Interrupt& accessUsartTxInterrupt<2>() noexcept { return usartTxIrq2; }
	template <> inline constexpr Interrupt& accessUsartTxInterrupt<3>() noexcept { return usartTxIrq3; }

	///Access the Usart UDRE-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	template <uint8_t Index> inline constexpr Interrupt& accessUsartUdreInterrupt() noexcept;
	template <> inline constexpr Interrupt& accessUsartUdreInterrupt<0>() noexcept { return usartUdreIrq0; }
	template <> inline constexpr Interrupt& accessUsartUdreInterrupt<1>() noexcept { return usartUdreIrq1; }
	template <> inline constexpr Interrupt& accessUsartUdreInterrupt<2>() noexcept { return usartUdreIrq2; }
	template <> inline constexpr Interrupt& accessUsartUdreInterrupt<3>() noexcept { return usartUdreIrq3; }
}


#endif /* SRC_RESOURCES_M2560_INTERRUPTS_H_ */
