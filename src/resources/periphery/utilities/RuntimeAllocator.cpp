#include "RuntimeAllocator.h"
#include "../../Periphery.h"
#include <util/atomic.h>


static uint8_t portUsage[Periphery::getCapacity<Port>()] = {}; //Initialize with 0's
static uint8_t usartUsage = 0;
static uint8_t gpiorUsage[Periphery::getCapacity<GeneralPurposeRegister>()] = {}; //Initialize with 0's
static uint8_t timerUsage = 0;
static uint8_t pcIntUsage = 0;
static uint8_t twiUsage = 0;
static uint8_t adcUsage = 0;
static bool watchdogUsage = false;
static bool eepromUsage = false;


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

inline bool allocateMask(uint8_t& byte, uint8_t mask) noexcept {
	bool success = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (! (byte & mask)) {
			byte |= mask;
			success = true;
		}
	}
	return success;
}

inline bool allocateBit(uint8_t& byte, uint8_t bit) noexcept {
	return allocateMask(byte, 1 << bit);
}


//-------------------------------------------------------------------------------------------

bool RuntimeAllocator::allocate(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateByte(portUsage[index]);
}

bool RuntimeAllocator::allocate(const Port* object, uint8_t mask) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateMask(portUsage[index], mask);
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

bool RuntimeAllocator::allocate(const Timer8bit* object) noexcept {
	uint8_t index = object->timerIndex;
	return allocateBit(timerUsage, index);
}

bool RuntimeAllocator::allocate(const Timer16bit* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateBit(timerUsage, index);
}

bool RuntimeAllocator::allocate(const PinChangeInterrupt* object) noexcept {
	uint8_t index = object->pinCangeInterruptIndex;
	return allocateBit(pcIntUsage, index);
}

bool RuntimeAllocator::allocate(const Twi* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateBit(twiUsage, index);
}

bool RuntimeAllocator::allocate(const Adc* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return allocateBit(adcUsage, index);
}

bool RuntimeAllocator::allocate(const Watchdog* object) noexcept {
	if (watchdogUsage) {
		return false;
	}
	watchdogUsage = true;
	return true;
}

bool RuntimeAllocator::allocate(const Eeprom* object) noexcept {
	if (eepromUsage) {
		return false;
	}
	eepromUsage = true;
	return true;
}

//-------------------------------------------------------------------------------------------

void RuntimeAllocator::deallocate(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	portUsage[index] = 0;
}

void RuntimeAllocator::deallocate(const Port* object, uint8_t mask) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	portUsage[index] &= ~mask;
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

void RuntimeAllocator::deallocate(const PinChangeInterrupt* object) noexcept {
	uint8_t index = object->pinCangeInterruptIndex;
	pcIntUsage &= ~(1 << index);
}

void RuntimeAllocator::deallocate(const Twi* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	twiUsage &= ~(1 << index);
}

void RuntimeAllocator::deallocate(const Adc* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	adcUsage &= ~(1 << index);
}

void RuntimeAllocator::deallocate(const Watchdog* object) noexcept {
	watchdogUsage = false;
}

void RuntimeAllocator::deallocate(const Eeprom* object) noexcept {
	eepromUsage = false;
}

//-------------------------------------------------------------------------------------------

bool RuntimeAllocator::isAllocated(const Port* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return portUsage[index] != 0;
}

bool isAllocated(const Port* object, uint8_t mask) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return (portUsage[index] & mask) != 0;
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

bool RuntimeAllocator::isAllocated(const PinChangeInterrupt* object) noexcept {
	uint8_t index = object->pinCangeInterruptIndex;
	return pcIntUsage & (1 << index);
}

bool RuntimeAllocator::isAllocated(const Twi* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return twiUsage & (1 << index);
}

bool RuntimeAllocator::isAllocated(const Adc* object) noexcept {
	uint8_t index = AddressMap::getIdentity(object);
	return adcUsage & (1 << index);
}

bool RuntimeAllocator::isAllocated(const Watchdog* object) noexcept {
	return watchdogUsage;
}

bool RuntimeAllocator::isAllocated(const Eeprom* object) noexcept {
	return eepromUsage;
}

