#include "RuntimeAllocator.h"
#include "../../Periphery.h"
#include <util/atomic.h>


static uint8_t portUsage[Periphery::getCapacity<Port>()] = {}; //Initialize with 0's
static uint8_t usartUsage = 0;
static uint8_t gpiorUsage[Periphery::getCapacity<GeneralPurposeRegister>()] = {}; //Initialize with 0's

//-------------------------------------------------------------------------------------------

bool RuntimeAllocator::allocate(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (portUsage[index] == 0) {
			portUsage[index] = 0xFF; //Set all Pins in use
			success = true;
		}
	}
	return success;
}

bool RuntimeAllocator::allocate(const Pin* object) noexcept { //Allocates part of underlying Port
	uint8_t index = AddressMap::getIdentity(&(object->port));
	uint8_t mask = 1 << object->getPinNumber();
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (! (portUsage[index] & mask)) {
			portUsage[index] |= mask;
			success = true;
		}
	}
	return success;
}

bool RuntimeAllocator::allocate(const Usart* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (usartUsage & (1 << index)) {
			usartUsage |= (1 << index);
			success = true;
		}
	}
	return success;
}

bool RuntimeAllocator::allocate(const GeneralPurposeRegister* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (gpiorUsage[index] == 0) {
			gpiorUsage[index] = 0xFF; //Set all Bits in use
			success = true;
		}
	}
	return success;
}

bool RuntimeAllocator::allocate(const GeneralPurposeFlag* object) noexcept { //Allocates part of underlying GeneralPurposeRegister
	uint8_t index = AddressMap::getIdentity(&(object->gpior));
	uint8_t mask = 1 << object->getBitNumber();
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (! (gpiorUsage[index] & mask)) {
			gpiorUsage[index] |= mask;
			success = true;
		}
	}
	return success;
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
