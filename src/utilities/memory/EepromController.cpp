#include "EepromController.hpp"
#include <util/atomic.h>

bool EepromController::write(uintptr_t adr, uint8_t* obj, uint8_t size) noexcept {
	if (!this->isBusy()) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			this->writeBuffer.object.pointer = obj;
			this->writeBuffer.object.size = size;
			this->status = WriteStatus::PlaneObject;
			this->enableEepromInterrupt();
			this->setEepromAddress(adr);
			this->setEepromData(*obj);
			this->triggerEepromWrite();
		}
		return true;
	}
	else {
		return false;
	}
}
