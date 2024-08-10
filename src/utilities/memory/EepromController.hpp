#ifndef SRC_UTILITIES_MEMORY_EEPROMCONTROLLER_HPP_
#define SRC_UTILITIES_MEMORY_EEPROMCONTROLLER_HPP_


#include <stdint.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include "../streaming/Stream.hpp"


#ifndef EEMEM
#define EEMEM __attribute__((section(".eeprom")))
#endif


class EepromController {

private:
	enum WriteStatus : uint8_t {
		Idle = 0,
		PlaneObject = 1,
		String = 2,
		StreamObject = 3
	} volatile status;

	union WriteBuffer {
		struct Object {
			volatile uint8_t* pointer;
			volatile uint8_t size;
		} object;
		Stream<uint8_t>* stream;
		const char* string;
	} writeBuffer;

	inline static void enableEepromInterrupt() noexcept {
		EECR |= (1 << EERIE);
	}

	inline static void disableEepromInterrupt() noexcept {
		EECR &= ~(1 << EERIE);
	}

	inline static void triggerEepromWrite() noexcept {
		EECR |= (1 << EEMPE);
		EECR |= (1 << EEPE);
	}

	inline static void triggerEepromRead() noexcept {
		EECR |= (1 << EERE);
	}

	inline static void setEepromAddress(uintptr_t adr) noexcept {
		EEAR = adr;
	}

	inline static void setEepromData(uint8_t data) noexcept {
		EEDR = data;
	}

	inline static uint8_t getEepromData() noexcept {
		return EEDR;
	}

	inline static void incrementEepromAddress() noexcept {
		EEAR++;
	}

	inline static void decrementEepromAddress() noexcept {
		EEAR--;
	}

	inline void eepromReadyCallback() noexcept {
		switch (this->status) {
		case WriteStatus::PlaneObject:
			this->writeBuffer.object.size--;
			if (this->writeBuffer.object.size > 0) {
				this->writeBuffer.object.pointer++;
				this->setEepromData(*this->writeBuffer.object.pointer);
				break;
			}
			else {
				this->status = WriteStatus::Idle; //Done
				return;
			}
		case WriteStatus::String:
			this->setEepromData(*this->writeBuffer.string);
			if (*this->writeBuffer.string == 0) {
				this->status = WriteStatus::Idle; //Done
			}
			this->writeBuffer.string++;
			break; //continue to write out 0-terminator
		case WriteStatus::StreamObject:
			if (this->writeBuffer.stream->hasNextStreamToken()) {
				this->setEepromData(this->writeBuffer.stream->getNextStreamToken());
				break;
			}
			else {
				this->status = WriteStatus::Idle; //Done
				return;
			}
		default: //Idle:
			this->disableEepromInterrupt();
			return;
		}
		this->incrementEepromAddress();
		this->triggerEepromWrite();
	}

	bool write(uintptr_t adr, uint8_t* obj, uint8_t size) noexcept;

	inline void read(uintptr_t adr, uint8_t* buf, uint8_t size) noexcept {
		for (uint8_t i = 0; i < size; i++) {
			this->setEepromAddress(adr++);
			this->triggerEepromRead();
			buf[i] = this->getEepromData();
		}
	}

	inline EepromController(Interrupt eepromIrq) noexcept : status(Idle) {
		eepromIrq.registerMethod<EepromController, &EepromController::eepromReadyCallback>(*this);
		EECR = 0;
	}

public:
	inline static EepromController& GetInstance() noexcept {
		static EepromController instance(Interrupts::getEepromInterrupt());
		return instance;
	}

	inline bool isBusy() noexcept {
		return (EECR & (1<<EEPE)) || (this->status != WriteStatus::Idle);
	}

	template<typename T> inline bool write(uintptr_t adr, T* obj) noexcept {
		return this->write(adr, reinterpret_cast<uint8_t*>(obj), sizeof(T));
	}

	inline bool write(uintptr_t adr, const char* string) noexcept {
		if (!this->isBusy() && (string != nullptr)) {
			this->writeBuffer.string = string;
			this->status = WriteStatus::String;
			this->setEepromAddress(adr-1);
			this->enableEepromInterrupt();
			return true;
		}
		else {
			return false;
		}
	}

	inline bool write(uintptr_t adr, Stream<uint8_t>* stream) noexcept {
		if (!this->isBusy()) {
			this->writeBuffer.stream = stream;
			this->status = WriteStatus::StreamObject;
			this->setEepromAddress(adr-1);
			this->enableEepromInterrupt();
			return true;
		}
		else {
			return false;
		}
	}

	inline bool write(uintptr_t adr, uint8_t data) noexcept {
		return this->write(adr, &data, 1);
	}

	template<typename T> inline bool syncWrite(uintptr_t adr, T* obj) noexcept {
		if(this->write<T>(adr, obj)) {
			while(this->isBusy());
			return true;
		}
		else {
			return false;
		}
	}

	inline bool syncWrite(uintptr_t adr, const char* string) noexcept {
		if (!this->write(adr, string)) {
			while(this->isBusy());
			return true;
		}
		else {
			return false;
		}
	}

	inline bool syncWrite(uintptr_t adr, Stream<uint8_t>* stream) noexcept {
		if (!this->write(adr, stream)) {
			while(this->isBusy());
			return true;
		}
		else {
			return false;
		}
	}

	inline bool syncWrite(uintptr_t adr, uint8_t data) noexcept {
		if (!this->write(adr, data)) {
			while(this->isBusy());
			return true;
		}
		else {
			return false;
		}
	}

	template<typename T> inline void read(uintptr_t adr, T* buf) noexcept {
		this->read(adr, reinterpret_cast<uint8_t*>(buf), sizeof(T));
	}

	inline uint8_t read(uintptr_t adr) noexcept {
		if (this->isBusy()) {
			return 0;
		}
		this->setEepromAddress(adr);
		this->triggerEepromRead();
		return this->getEepromData();
	}
};


#endif /* SRC_UTILITIES_MEMORY_EEPROMCONTROLLER_HPP_ */
