#ifndef SRC_RESOURCES_PERIPHERY_UTILITIES_RUNTIMEALLOCATOR_H_
#define SRC_RESOURCES_PERIPHERY_UTILITIES_RUNTIMEALLOCATOR_H_


#include <stdint.h>


//Forward Declarations
class Port;
class Pin;
class Usart;
class GeneralPurposeRegister;
class GeneralPurposeFlag;
class Timer8bit;
class Timer16bit;
class PinChangeInterrupt;
class Twi;


namespace RuntimeAllocator {

	bool allocate(const Port* object) noexcept;
	bool allocate(const Port* object, uint8_t mask) noexcept;
	bool allocate(const Pin* object) noexcept;
	bool allocate(const Usart* object) noexcept;
	bool allocate(const GeneralPurposeRegister* object) noexcept;
	bool allocate(const GeneralPurposeFlag* object) noexcept;
	bool allocate(const Timer8bit* object) noexcept;
	bool allocate(const Timer16bit* object) noexcept;
	bool allocate(const PinChangeInterrupt* object) noexcept;
	bool allocate(const Twi* object) noexcept;

	void deallocate(const Port* object) noexcept;
	void deallocate(const Port* object, uint8_t mask) noexcept;
	void deallocate(const Pin* object) noexcept;
	void deallocate(const Usart* object) noexcept;
	void deallocate(const GeneralPurposeRegister* object) noexcept;
	void deallocate(const GeneralPurposeFlag* object) noexcept;
	void deallocate(const Timer8bit* object) noexcept;
	void deallocate(const Timer16bit* object) noexcept;
	void deallocate(const PinChangeInterrupt* object) noexcept;
	void deallocate(const Twi* object) noexcept;

	bool isAllocated(const Port* object) noexcept;
	bool isAllocated(const Port* object, uint8_t mask) noexcept;
	bool isAllocated(const Pin* object) noexcept;
	bool isAllocated(const Usart* object) noexcept;
	bool isAllocated(const GeneralPurposeRegister* object) noexcept;
	bool isAllocated(const GeneralPurposeFlag* object) noexcept;
	bool isAllocated(const Timer8bit* object) noexcept;
	bool isAllocated(const Timer16bit* object) noexcept;
	bool isAllocated(const PinChangeInterrupt* object) noexcept;
	bool isAllocated(const Twi* object) noexcept;
}


#endif /* SRC_RESOURCES_PERIPHERY_UTILITIES_RUNTIMEALLOCATOR_H_ */
