#ifndef SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_
#define SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include "../scheduling/AsynchronousTask.hpp"


class I2cMaster {

private:
	Twi& twi;

	AsynchronousTask<void>* errorCallback;

	struct Operation {
		enum Mode : int8_t {
			writeSingleData = -1,
			writeArrayData = 0,
			readData = 1
		} mode;
		union Data {
			uint8_t single;
			uint8_t* array;
			Data(uint8_t single) noexcept : single(single) {}
			Data(uint8_t* array) noexcept : array(array) {}
		} volatile data;
		volatile uint8_t slaveAddress;
		volatile uint8_t registerAddress;
		volatile uint8_t length = 0; //decrementing counter, 0 when completed
		AsynchronousTask<void>* completionCallback;
		inline void set(Mode mode, Data data, uint8_t slaveAddress, uint8_t registerAddress, uint8_t length, AsynchronousTask<void>* completionCallback) noexcept {
			this->slaveAddress = (slaveAddress << 1);
			this->registerAddress = registerAddress;
			this->data = data;
			this->mode = mode;
			this->length = length;
			this->completionCallback = completionCallback;
		}
	} operation;

	enum Status : int8_t {
		Idle = 0,
		Busy = 1,
		BusError = -1,
		ArbitrationLost = -2,
		AddressNack = -3,
		DataNack = -4,
		TransmissionError = -5
	} volatile status;


	inline void twiStart() noexcept {
		this->twi.scheduleStart();
		this->twi.clearInterruptFlag();
	}

	inline void twiCallback() noexcept {
		switch (this->twi.getStatus()) {
		case Twi::TWSReg::FIELDS::Status::BusError:
			this->status = Status::BusError;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::Idle:
			break;
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost:
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost_Broadcast:
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost_SLA_R:
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost_SLA_W:
			this->status = Status::ArbitrationLost;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataReceived_NACK:
		case Twi::TWSReg::FIELDS::Status::M_DataTransmitted_NACK:
			this->status = Status::DataNack;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_R_NACK:
		case Twi::TWSReg::FIELDS::Status::M_SLA_W_NACK:
			this->status = Status::AddressNack;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::M_StartTransmitted:
			this->twi.clearStart();
			this->twi.setData(this->operation.slaveAddress); //Prepare SLA+W
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_RepeatedStartTransmitted:
			this->twi.clearStart();
			this->twi.setData(this->operation.slaveAddress | 0x01); //Prepare SLA+R
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_W_ACK:
			this->twi.setData(this->operation.registerAddress);
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataTransmitted_ACK:
			if (this->operation.mode == Operation::Mode::readData) {
				this->twi.scheduleStart(); //Prepare Repeated Start for Reading
			}
			else if (this->operation.length > 0) {
				if (this->operation.mode == Operation::Mode::writeSingleData) {
					this->twi.setData(this->operation.data.single);
					this->operation.length = 0;
				}
				else {
					this->twi.setData(*this->operation.data.array);
					this->operation.data.array++;
					this->operation.length--;
				}
			}
			else {
				this->status = Status::Idle;
				if (this->operation.completionCallback != nullptr) {
					this->operation.completionCallback->execute<REPEATEDLY>();
				}
				this->twi.stop();
			}
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_R_ACK:
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataReceived_ACK:
			*this->operation.data.array = twi.readData();
			this->operation.length--;
			if (this->operation.length > 0) {
				this->operation.data.array++;
			}
			if (this->operation.length == 0) {
				this->status = Status::Idle;
				if (this->operation.completionCallback != nullptr) {
					this->operation.completionCallback->execute<REPEATEDLY>();
				}
				this->twi.stop();
			}
			this->twi.clearInterruptFlag();
			break;
		default:
			this->status = Status::TransmissionError;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			break;
		}
	}

public:

	enum Speed : uint8_t {
		Slow10k = 1,
		Normal100k = 10,
		High400k = 40
	};

	inline I2cMaster(Twi& twi, Interrupt twiIrq) noexcept: twi(twi), errorCallback(nullptr), operation({}), status(Status::Idle) {
		twiIrq.registerMethod<I2cMaster, &I2cMaster::twiCallback>(*this);
	}

	inline void init() noexcept { this->twi.init(); }
	inline void close() noexcept { this->twi.close(); }

	template <uint32_t FCPU> inline void configure(Speed speed, bool internalPullup = false) noexcept {
		uint32_t fScl = uint32_t(10000)*speed;
		uint32_t scale = ((FCPU/fScl)-16)/2;

		if (scale < 256) {
			this->twi.setPrescalar(Twi::TWSReg::FIELDS::Prescaler::Prescale_1);
			this->twi.setBitRate(scale);
		}
		else if (scale < 1024) {
			this->twi.setPrescalar(Twi::TWSReg::FIELDS::Prescaler::Prescale_4);
			this->twi.setBitRate(scale/4);
		}
		else if (scale < 4096) {
			this->twi.setPrescalar(Twi::TWSReg::FIELDS::Prescaler::Prescale_16);
			this->twi.setBitRate(scale/16);
		}
		else {
			this->twi.setPrescalar(Twi::TWSReg::FIELDS::Prescaler::Prescale_64);
			this->twi.setBitRate(scale/64);
		}

		if (internalPullup) {
			Periphery::getTwiSclPin().setMode(Pin::Mode::INPUT_PULLUP);
			Periphery::getTwiSdaPin().setMode(Pin::Mode::INPUT_PULLUP);
		}
	}

	inline void enable() noexcept {
		this->twi.enable();
		this->twi.enableInterrupt();
		this->twi.enableAck();
	}

	inline void disable() noexcept {
		this->twi.disable();
		this->twi.disableInterrupt();
	}

	inline bool writeAsync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t data, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (this->status == Status::Idle) {
			this->status = Status::Busy;
			this->operation.set(Operation::Mode::writeSingleData, Operation::Data(data), slaveAddress, slaveRegister, 1, completionCallback);
			this->twiStart();
			return true;
		}
		return false;
	}

	inline bool writeAsync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* data, uint8_t length, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (length > 0) {
			if (this->status == Status::Idle) {
				this->status = Status::Busy;
				this->operation.set(Operation::Mode::writeArrayData, Operation::Data(data), slaveAddress, slaveRegister, length, completionCallback);
				this->twiStart();
				return true;
			}
		}
		return false;
	}

	inline bool readAsync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* buffer, uint8_t length = 1, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (length > 0) {
			if (this->status == Status::Idle) {
				this->status = Status::Busy;
				this->operation.set(Operation::Mode::readData, Operation::Data(buffer), slaveAddress, slaveRegister, length, completionCallback);
				this->twiStart();
				return true;
			}
		}
		return false;
	}

	inline uint8_t readByteSync(uint8_t slaveAddress, uint8_t slaveRegister) noexcept {
		uint8_t buffer;
		struct Lock {
			volatile bool wait = true;
			inline void resume() noexcept { this->wait = false; }
		} lock;
		AsynchronousTask<void> completionCallback = AsynchronousTask<void>();
		completionCallback.scheduleMethod<Lock, &Lock::resume>(lock);
		if (!readAsync(slaveAddress, slaveRegister, &buffer, 1, &completionCallback)) {
			return 0;
		}
		while (lock.wait) {
			if (this->hasError()) {
				return 0;
			}
		}
		return buffer;
	}

	inline Status getBusStatus() const noexcept {
		return this->status;
	}

	inline bool hasError() const noexcept {
		return this->status < Status::Idle;
	}

	inline bool isIdle() const noexcept {
		return this->status == Status::Idle;
	}

	inline bool isBusy() const noexcept {
		return this->status == Status::Busy;
	}

	inline void clearError() noexcept {
		this->operation.length = 0;
		this->status = Status::Idle;
		this->twi.stop(); //TransmissionError recovery
		this->twi.clearInterruptFlag();
	}

	inline void setErrorCallback(AsynchronousTask<void>* errorCallback) noexcept {
		this->errorCallback = errorCallback;
	}

};


#endif /* SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_ */
