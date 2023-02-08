#include "RuntimeAllocator.h"
#include "../../Periphery.h"
#include <util/atomic.h>


static uint8_t portUsage[Periphery::getCapacity<Port>()] = {}; //Initialize with 0's
static uint8_t usartUsage = 0;
static uint8_t gpiorUsage[Periphery::getCapacity<GeneralPurposeRegister>()] = {}; //Initialize with 0's
static uint8_t timerUsage = 0;


inline bool allocateByte(uint8_t& byte) noexcept {
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (byte == 0) {
			byte = 0xFF; //Set all Bits in use
			success = true;
		}
	}
	return success;
}

inline bool allocateBit(uint8_t& byte, uint8_t bit) noexcept {
	bool success = false;
	uint8_t mask = 1 << bit;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (! (byte & mask)) {
			byte |= mask;
			success = true;
		}
	}
	return success;
}


//-------------------------------------------------------------------------------------------

bool RuntimeAllocator::allocate(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateByte(portUsage[index]);
}

bool RuntimeAllocator::allocate(const Pin* object) noexcept { //Allocates part of underlying Port
	uint8_t index = AddressMap::getIdentity(&(object->port));
	return allocateBit(portUsage[index], object->getPinNumber());
}

bool RuntimeAllocator::allocate(const Usart* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateBit(usartUsage, index);
}

bool RuntimeAllocator::allocate(const GeneralPurposeRegister* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateByte(gpiorUsage[index]);
}

bool RuntimeAllocator::allocate(const GeneralPurposeFlag* object) noexcept { //Allocates part of underlying GeneralPurposeRegister
	uint8_t index = AddressMap::getIdentity(&(object->gpior));
	return allocateBit(gpiorUsage[index], object->getBitNumber());
}

bool RuntimeAllocator::allocate(const Timer8bit* object) noexcept { //Allocates part of underlying GeneralPurposeRegister
	uint8_t index = object->timerIndex;
	return allocateBit(timerUsage, index);
}

bool RuntimeAllocator::allocate(const Timer16bit* object) noexcept { //Allocates part of underlying GeneralPurposeRegister
	uint8_t index = AddressMap::getIdentity(object);
	return allocateBit(timerUsage, index);
}

//-------------------------------------------------------------------------------------------

void RuntimeAllocator::deallocate(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	portUsage[index] = 0;
}

void RuntimeAllocator::deallocate(const Pin* object) noexcept { //Deallocates part of underlying Port
	uint8_t index = AddressMap::getIdentity(&(object->port));
	uint8_t mask = 1 << object->getPinNumber();
	portUsage[index] &= ~mask;
}

void RuntimeAllocator::deallocate(const Usart* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	usartUsage &= ~(1 << index);
}

void RuntimeAllocator::deallocate(const GeneralPurposeRegister* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	gpiorUsage[index] = 0;
}

void RuntimeAllocator::deallocate(const GeneralPurposeFlag* object) noexcept { //Deallocates part of underlying GeneralPurposeRegister
	uint8_t index = AddressMap::getIdentity(&(object->gpior));
	uint8_t mask = 1 << object->getBitNumber();
	gpiorUsage[index] &= ~mask;
}

void RuntimeAllocator::deallocate(const Timer8bit* object) noexcept {
	uint8_t index = object->timerIndex;
	timerUsage &= ~(1 << index);
}

void RuntimeAllocator::deallocate(const Timer16bit* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	timerUsage &= ~(1 << index);
}

//-------------------------------------------------------------------------------------------

bool RuntimeAllocator::isAllocated(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return portUsage[index] != 0;
}

bool RuntimeAllocator::isAllocated(const Pin* object) noexcept { //Checks part of underlying Port
	uint8_t index = AddressMap::getIdentity(&(object->port));
	uint8_t mask = 1 << object->getPinNumber();
	return (portUsage[index] & mask) != 0;
}

bool RuntimeAllocator::isAllocated(const Usart* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return usartUsage & (1 << index);
}

bool RuntimeAllocator::isAllocated(const GeneralPurposeRegister* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return gpiorUsage[index] != 0;
}

bool RuntimeAllocator::isAllocated(const GeneralPurposeFlag* object) noexcept { //Checks part of underlying GeneralPurposeRegister
	uint8_t index = AddressMap::getIdentity(&(object->gpior));
	uint8_t mask = 1 << object->getBitNumber();
	return (gpiorUsage[index] & mask) != 0;
}

bool RuntimeAllocator::isAllocated(const Timer8bit* object) noexcept {
	uint8_t index = object->timerIndex;
	return timerUsage & (1 << index);
}

bool RuntimeAllocator::isAllocated(const Timer16bit* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return timerUsage & (1 << index);
}

