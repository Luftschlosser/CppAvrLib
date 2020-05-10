#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_

//_____________________________________________
//TYPES:

//Types of Interrupt-Class-Implementations
#define NONE 0
#define UNIVERSAL 1 //Implementation supports both C-Style Callback and Object oriented Trigger-Interface
#define CALLBACK 2 //Implementation supports only C-Style Callback
#define TRIGGER 3 //Implementation supports only Object oriented Trigger-Interface

//Types of ISR-Routine-Implementations
#define NONE 0
#define BLOCK 1
#define NOBLOCK 2

//Types of Default-Implementations for uninitialized Listeners when using Interrupt-Type "Trigger"
#define INSERT_CHECK 0
#define EMPTY_LISTENER 1

//_____________________________________________
//CONFIGURATION:

//Configuration of general Interrupt-Implementation
#define INTERRUPTTYPE UNIVERSAL

//Configuration of Default-Implementation for uninitialized Listeners when using Interrupt-Type "Trigger"
#define DEFAULT_TRIGGER_BEHAVIOR EMPTY_LISTENER

//Implementation Type configuration for each Interrupt source
#define ISRTYPE_USART0_RX BLOCK
#define ISRTYPE_USART0_TX BLOCK
#define ISRTYPE_USART0_UDRE BLOCK
#define ISRTYPE_USART1_RX BLOCK
#define ISRTYPE_USART1_TX BLOCK
#define ISRTYPE_USART1_UDRE BLOCK
#define ISRTYPE_USART2_RX BLOCK
#define ISRTYPE_USART2_TX BLOCK
#define ISRTYPE_USART2_UDRE BLOCK
#define ISRTYPE_USART3_RX BLOCK
#define ISRTYPE_USART3_TX BLOCK
#define ISRTYPE_USART3_UDRE BLOCK


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_ */
