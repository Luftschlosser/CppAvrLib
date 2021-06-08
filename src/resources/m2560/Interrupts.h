#ifndef SRC_RESOURCES_M2560_INTERRUPTS_H_
#define SRC_RESOURCES_M2560_INTERRUPTS_H_


#include "../interrupts/Interrupt.h"


///Interrupt declaration for the ATmega2560
namespace Interrupts {

	static Interrupt externalInterrupt0 = Interrupt::Create<INT0_vect_num>();
	static Interrupt externalInterrupt1 = Interrupt::Create<INT1_vect_num>();
	static Interrupt externalInterrupt2 = Interrupt::Create<INT2_vect_num>();
	static Interrupt externalInterrupt3 = Interrupt::Create<INT3_vect_num>();
	static Interrupt externalInterrupt4 = Interrupt::Create<INT4_vect_num>();
	static Interrupt externalInterrupt5 = Interrupt::Create<INT5_vect_num>();
	static Interrupt externalInterrupt6 = Interrupt::Create<INT6_vect_num>();
	static Interrupt externalInterrupt7 = Interrupt::Create<INT7_vect_num>();

	static Interrupt usartRxIrq0 = Interrupt::Create<USART0_RX_vect_num>();
	static Interrupt usartRxIrq1 = Interrupt::Create<USART1_RX_vect_num>();
	static Interrupt usartRxIrq2 = Interrupt::Create<USART2_RX_vect_num>();
	static Interrupt usartRxIrq3 = Interrupt::Create<USART3_RX_vect_num>();

	static Interrupt usartTxIrq0 = Interrupt::Create<USART0_TX_vect_num>();
	static Interrupt usartTxIrq1 = Interrupt::Create<USART1_TX_vect_num>();
	static Interrupt usartTxIrq2 = Interrupt::Create<USART2_TX_vect_num>();
	static Interrupt usartTxIrq3 = Interrupt::Create<USART3_TX_vect_num>();

	static Interrupt usartUdreIrq0 = Interrupt::Create<USART0_UDRE_vect_num>();
	static Interrupt usartUdreIrq1 = Interrupt::Create<USART1_UDRE_vect_num>();
	static Interrupt usartUdreIrq2 = Interrupt::Create<USART2_UDRE_vect_num>();
	static Interrupt usartUdreIrq3 = Interrupt::Create<USART3_UDRE_vect_num>();


	///Access the Interrupt object for the external Interrupt with the given index
	///\param index the index of the external Interrupt
	///\return A reference to the Interrupt object
	inline constexpr Interrupt& accessExternalInterrupt(uint8_t index) noexcept {
		switch (index) {
		case 0:
			return externalInterrupt0;
		case 1:
			return externalInterrupt1;
		case 2:
			return externalInterrupt2;
		case 3:
			return externalInterrupt3;
		case 4:
			return externalInterrupt4;
		case 5:
			return externalInterrupt5;
		case 6:
			return externalInterrupt6;
		default: //case 7:
			return externalInterrupt7;
		}
	}

	///Access the Usart RX-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	inline constexpr Interrupt& accessUsartRxInterrupt(uint8_t index) noexcept {
		switch (index) {
		case 0:
			return usartRxIrq0;
		case 1:
			return usartRxIrq1;
		case 2:
			return usartRxIrq2;
		default: //case 3:
			return usartRxIrq3;
		}
	}

	///Access the Usart TX-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	inline constexpr Interrupt& accessUsartTxInterrupt(uint8_t index) noexcept {
		switch (index) {
		case 0:
			return usartTxIrq0;
		case 1:
			return usartTxIrq1;
		case 2:
			return usartTxIrq2;
		default: //case 3:
			return usartTxIrq3;
		}
	}

	///Access the Usart UDRE-Interrupt object for the Usart device with the given index
	///\param index the index of the Usart [0-3]
	///\return A reference to the Interrupt object
	inline constexpr Interrupt& accessUsartUdreInterrupt(uint8_t index) noexcept {
		switch (index) {
		case 0:
			return usartUdreIrq0;
		case 1:
			return usartUdreIrq1;
		case 2:
			return usartUdreIrq2;
		default: //case 3:
			return usartUdreIrq3;
		}
	}
}


#endif /* SRC_RESOURCES_M2560_INTERRUPTS_H_ */
