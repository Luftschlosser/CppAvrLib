#ifndef SRC_RESOURCES_CONFIGURATION_H_
#define SRC_RESOURCES_CONFIGURATION_H_

//_____________________________________________
//BEHAVIOR:

namespace Configuration {

	///Flag to enable/disable periphery runtime allocations
	static constexpr bool runtimeAllocationsEnabled = true;

}

//_____________________________________________
//INTERRUPT-TYPES:

//Types of ISR-Routine-Implementations
#define NONE 0
#define BLOCK 1
#define NOBLOCK 2

//_____________________________________________
//INTERRUPT-CONFIGURATION:

//Implementation Type configuration for each Interrupt source [NONE / BLOCK / NOBLOCK]
#define ISRTYPE_EXT_INT0 BLOCK
#define ISRTYPE_EXT_INT1 NONE
#define ISRTYPE_EXT_INT2 NONE
#define ISRTYPE_EXT_INT3 NONE
#define ISRTYPE_EXT_INT4 NONE
#define ISRTYPE_EXT_INT5 NONE
#define ISRTYPE_EXT_INT6 NONE
#define ISRTYPE_EXT_INT7 NONE

#define ISRTYPE_USART0_RX BLOCK
#define ISRTYPE_USART0_TX BLOCK
#define ISRTYPE_USART0_UDRE BLOCK
#define ISRTYPE_USART1_RX NONE
#define ISRTYPE_USART1_TX NONE
#define ISRTYPE_USART1_UDRE NONE
#define ISRTYPE_USART2_RX NONE
#define ISRTYPE_USART2_TX NONE
#define ISRTYPE_USART2_UDRE NONE
#define ISRTYPE_USART3_RX NONE
#define ISRTYPE_USART3_TX NONE
#define ISRTYPE_USART3_UDRE NONE


#endif /* SRC_RESOURCES_CONFIGURATION_H_ */
