#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_


//Types of Interrupt-Implementations
#define UNIVERSAL 0 //Implementation supports both C-Style Callback and Object oriented Trigger-Interface
#define CALLBACK 1 //Implementation supports only C-Style Callback
#define TRIGGER 2 //Implementation supports only Object oriented Trigger-Interface
#define NONE 3 //Implementation is up to the User

//Implementation Type specification for each Interrupt source
#define ISRTYPE_USART0_RX UNIVERSAL
#define ISRTYPE_USART0_TX UNIVERSAL
#define ISRTYPE_USART0_UDRE UNIVERSAL
#define ISRTYPE_USART1_RX UNIVERSAL
#define ISRTYPE_USART1_TX UNIVERSAL
#define ISRTYPE_USART1_UDRE UNIVERSAL
#define ISRTYPE_USART2_RX UNIVERSAL
#define ISRTYPE_USART2_TX UNIVERSAL
#define ISRTYPE_USART2_UDRE UNIVERSAL
#define ISRTYPE_USART3_RX UNIVERSAL
#define ISRTYPE_USART3_TX UNIVERSAL
#define ISRTYPE_USART3_UDRE UNIVERSAL


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPTCONFIGURATION_H_ */
