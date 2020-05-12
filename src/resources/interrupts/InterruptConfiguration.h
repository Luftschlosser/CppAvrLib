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

//Configuration of general Interrupt-Implementation [NONE / UNIVERSAL / CALLBACK / TRIGGER]
#define INTERRUPTTYPE UNIVERSAL

//Configuration of Default-Implementation for uninitialized Listeners when using Interrupt-Type "Trigger" [INSERT_CHECK / EMPTY_LISTENER]
#define DEFAULT_TRIGGER_BEHAVIOR INSERT_CHECK

//Implementation Type configuration for each Interrupt source [NONE / BLOCK / NOBLOCK]
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


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_ */
