#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_


//Types of Interrupt-Class-Implementations
#define UNIVERSAL 1 //Implementation supports both C-Style Callback and Object oriented Trigger-Interface
#define CALLBACK 2 //Implementation supports only C-Style Callback
#define TRIGGER 3 //Implementation supports only Object oriented Trigger-Interface

//Types of ISR-Routine-Implementations
#define BLOCK 1
#define NOBLOCK 2

//Implementation Type "no implementation" - Usable as ISR-Routine-Implementation-Type and as Interrupt-Class-Implementation-Type
#define NONE 0


//Type of general Interrupt-Implementation
#define INTERRUPTTYPE UNIVERSAL

//Implementation Type specification for each Interrupt source
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
