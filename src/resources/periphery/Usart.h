#ifndef SRC_RESOURCES_PERIPHERY_USART_H_
#define SRC_RESOURCES_PERIPHERY_USART_H_


#include <stdlib.h>
#include "../Periphery.h"


class Usart final {

private:
	volatile uint8_t ctrlA; //UCSRnA
	volatile uint8_t ctrlB; //UCSRnB
	volatile uint8_t ctrlC; //UCSRnC
	volatile const uint8_t reserved;
	volatile uint16_t baud; //UBRRn (H+L)
	volatile uint8_t data; //UDRn

	static uint8_t usage;

public:
	void init();
	void close() noexcept;
	bool isUsed() noexcept;
};


#endif /* SRC_RESOURCES_PERIPHERY_USART_H_ */
