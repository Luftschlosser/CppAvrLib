#ifndef SRC_RESOURCES_CONFIGURATION_H_
#define SRC_RESOURCES_CONFIGURATION_H_


namespace Configuration {

	///Flag to enable/disable periphery runtime allocations
	static constexpr bool runtimeAllocationsEnabled = true;

	///Flag to enable/disable automatic runtime allocation of Pins used by other periphery via alternate Port functions.
	static constexpr bool autoPinAllocationEnabled = true;

	///Flag to enable/disable automatic Data-Direction Configuration of Pins used by other periphery via alternate Port functions.
	static constexpr bool autoPinConfigurationEnabled = true;

	//TODO: Errorhandling config: None/Exceptions/Errorhandling/

	//Flags to enable/disable Interrupt-Instantiations (change "ISR.cpp" to remove ISR-routines completely)
	static constexpr bool enableInterrupt_EXT_INT0 		= true;
	static constexpr bool enableInterrupt_EXT_INT1 		= false;
	static constexpr bool enableInterrupt_EXT_INT2 		= false;
	static constexpr bool enableInterrupt_EXT_INT3 		= false;
	static constexpr bool enableInterrupt_EXT_INT4 		= false;
	static constexpr bool enableInterrupt_EXT_INT5 		= false;
	static constexpr bool enableInterrupt_EXT_INT6 		= false;
	static constexpr bool enableInterrupt_EXT_INT7 		= false;
	static constexpr bool enableInterrupt_USART0_RX 	= true;
	static constexpr bool enableInterrupt_USART0_TX 	= true;
	static constexpr bool enableInterrupt_USART0_UDRE 	= true;
	static constexpr bool enableInterrupt_USART1_RX 	= false;
	static constexpr bool enableInterrupt_USART1_TX 	= false;
	static constexpr bool enableInterrupt_USART1_UDRE 	= false;
	static constexpr bool enableInterrupt_USART2_RX 	= false;
	static constexpr bool enableInterrupt_USART2_TX 	= false;
	static constexpr bool enableInterrupt_USART2_UDRE 	= false;
	static constexpr bool enableInterrupt_USART3_RX 	= false;
	static constexpr bool enableInterrupt_USART3_TX 	= false;
	static constexpr bool enableInterrupt_USART3_UDRE 	= false;
	static constexpr bool enableInterrupt_TIMER0_OC_A	= true;
	static constexpr bool enableInterrupt_TIMER0_OC_B	= true;
	static constexpr bool enableInterrupt_TIMER0_OVF	= true;
	static constexpr bool enableInterrupt_TIMER2_OC_A	= false;
	static constexpr bool enableInterrupt_TIMER2_OC_B	= false;
	static constexpr bool enableInterrupt_TIMER2_OVF	= false;
}


#endif /* SRC_RESOURCES_CONFIGURATION_H_ */
