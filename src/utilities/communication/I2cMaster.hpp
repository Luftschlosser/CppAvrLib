#ifndef SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_
#define SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include "../scheduling/AsynchronousTask.hpp"


class I2cMaster {

public:
	enum Status : int8_t {
		Idle = 0,
		Busy = 1,
		BusError = -1,
		ArbitrationLost = -2,
		AddressNack = -3,
		DataNack = -4,
		TransmissionError = -5
	};

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
		} data;
		uint8_t slaveAddress;
		uint8_t registerAddress;
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
		Operation() noexcept : mode(Mode::writeArrayData), data(nullptr), slaveAddress(0), registerAddress(0), length(0), completionCallback(nullptr) {}
		Operation(Operation& other) noexcept : mode(other.mode), data(other.data), slaveAddress(other.slaveAddress), registerAddress(other.registerAddress),
				length(other.length), completionCallback(other.completionCallback) {}
	} operation;

	volatile Status status;


	inline void twiStart() noexcept {
		static const uint8_t TwiCtrl_TwintTwstaTwenTwie = 0xA5;
		this->twi.regTWCR.reg = TwiCtrl_TwintTwstaTwenTwie;
	}

	inline void twiStop() noexcept {
		static const uint8_t TwiCtrl_TwintTwstoTwen = 0x94;
		this->twi.regTWCR.reg = TwiCtrl_TwintTwstoTwen;
	}

	inline void twiResume() noexcept {
		static const uint8_t TwiCtrl_TwintTwenTwie = 0x85;
		this->twi.regTWCR.reg = TwiCtrl_TwintTwenTwie;
	}

	inline void twiResumeWithAck() noexcept {
		static const uint8_t TwiCtrl_TwintTweaTwenTwie = 0xC5;
		this->twi.regTWCR.reg = TwiCtrl_TwintTweaTwenTwie;
	}

	inline void twiCallback() noexcept {
		switch (this->twi.getStatus()) {
		case Twi::TWSReg::FIELDS::Status::BusError:
			this->status = Status::BusError;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			this->twiStop();
			break;
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost:
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost_Broadcast:
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost_SLA_R:
		case Twi::TWSReg::FIELDS::Status::M_ArbitrationLost_SLA_W:
			this->status = Status::ArbitrationLost;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			this->twiStop();
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataTransmitted_NACK:
			this->status = Status::DataNack;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			this->twiStop();
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_R_NACK:
		case Twi::TWSReg::FIELDS::Status::M_SLA_W_NACK:
			this->status = Status::AddressNack;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			this->twiStop();
			break;
		case Twi::TWSReg::FIELDS::Status::M_StartTransmitted:
			this->twi.setData(this->operation.slaveAddress); //Prepare SLA+W
			this->twiResume();
			break;
		case Twi::TWSReg::FIELDS::Status::M_RepeatedStartTransmitted:
			this->twi.setData(this->operation.slaveAddress | 0x01); //Prepare SLA+R
			this->twiResume();
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_W_ACK:
			this->twi.setData(this->operation.registerAddress);
			this->twiResume();
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataTransmitted_ACK:
			if (this->operation.mode == Operation::Mode::readData) {
				this->twiStart(); //Prepare repeated Start for Receiving
			}
			else if (this->operation.length > 0) {
				if (this->operation.mode == Operation::Mode::writeSingleData) {
					this->twi.setData(this->operation.data.single);
					this->operation.length = 0;
				}
				else {
					this->twi.setData(*(this->operation.data.array));
					(this->operation.data.array)++;
					this->operation.length--;
				}
				this->twiResume();
			}
			else {
				this->status = Status::Idle;
				if (this->operation.completionCallback != nullptr) {
					this->operation.completionCallback->execute<REPEATEDLY>();
				}
				this->twiStop();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_R_ACK:
			if (this->operation.length > 1) {
				this->twiResumeWithAck();
			}
			else {
				this->twiResume();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataReceived_ACK:
		case Twi::TWSReg::FIELDS::Status::M_DataReceived_NACK:
			*(this->operation.data.array) = twi.readData();
			this->operation.length--;
			if (this->operation.length > 0) {
				(this->operation.data.array)++;
				if (this->operation.length > 1) {
					this->twiResumeWithAck();
				}
				else {
					this->twiResume();
				}
			}
			else {
				this->status = Status::Idle;
				if (this->operation.completionCallback != nullptr) {
					this->operation.completionCallback->execute<REPEATEDLY>();
				}
				this->twiStop();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::Idle:
			break;
		default:
			this->status = Status::TransmissionError;
			if (this->errorCallback != nullptr) {
				this->errorCallback->execute<REPEATEDLY>();
			}
			this->twiStop();
			break;
		}
	}

public:

	enum Speed : uint8_t {
		Slow10k = 1,
		Normal100k = 10,
		High400k = 40
	};

	inline I2cMaster(Twi& twi, Interrupt twiIrq) noexcept : twi(twi), errorCallback(nullptr), operation(), status(Status::Idle) {
		twiIrq.registerMethod<I2cMaster, &I2cMaster::twiCallback>(*this);
	}
	inline I2cMaster(I2cMaster& copy) noexcept = delete; //Cannot copy, because Interrupt Callback is connected to original Object

	inline void init() noexcept { this->twi.init(); }
	inline void close() noexcept { this->twi.close(); }

	inline void configure(Speed speed, bool internalPullup = false) noexcept {
		uint32_t fScl = uint32_t(10000)*speed;
		uint32_t scale = ((F_CPU/fScl)-16)/2;

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
			Periphery::getTwiSclPin(this->twi.getIdentityIndex()).setMode(Pin::Mode::INPUT_PULLUP);
			Periphery::getTwiSdaPin(this->twi.getIdentityIndex()).setMode(Pin::Mode::INPUT_PULLUP);
		}
	}

	inline void enable() noexcept {
		this->twi.enable();
	}

	inline void disable() noexcept {
		this->twi.disable();
		this->twi.disableInterrupt();
	}

	inline bool writeAsync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t data, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (this->isIdle()) {
			this->status = Status::Busy;
			this->operation.set(Operation::Mode::writeSingleData, Operation::Data(data), slaveAddress, slaveRegister, 1, completionCallback);
			this->twiStart();
			return true;
		}
		return false;
	}

	inline bool writeAsync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* data, uint8_t length, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (length > 0) {
			if (this->isIdle()) {
				this->status = Status::Busy;
				this->operation.set(Operation::Mode::writeArrayData, Operation::Data(data), slaveAddress, slaveRegister, length, completionCallback);
				this->twiStart();
				return true;
			}
		}
		return false;
	}

	inline bool writeSync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t data) noexcept {
		if (this->writeAsync(slaveAddress, slaveRegister, data)) {
			while (!this->isIdle()) {
				if (this->hasError()) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	inline bool writeSync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* data, uint8_t length) noexcept {
		if (this->writeAsync(slaveAddress, slaveRegister, data, length)) {
			while (!this->isIdle()) {
				if (this->hasError()) {
					return false;
				}
			}
			return true;
		}
		return false;
	}

	inline bool readAsync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* buffer, uint8_t length = 1, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (length > 0) {
			if (this->isIdle()) {
				this->status = Status::Busy;
				this->operation.set(Operation::Mode::readData, Operation::Data(buffer), slaveAddress, slaveRegister, length, completionCallback);
				this->twiStart();
				return true;
			}
		}
		return false;
	}

	inline uint8_t readSync(uint8_t slaveAddress, uint8_t slaveRegister) noexcept {
		uint8_t buffer;
		if (readAsync(slaveAddress, slaveRegister, &buffer)) {
			while (!this->isIdle()) {
				if (this->hasError()) {
					return 0;
				}
			}
			return buffer;
		}
		return 0;
	}

	inline bool readSync(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* buffer, uint8_t length = 1) noexcept {
		if (readAsync(slaveAddress, slaveRegister, buffer, length)) {
			while (!this->isIdle()) {
				if (this->hasError()) {
					return false;
				}
			}
			return true;
		}
		return false;
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
	}

	inline void setErrorCallback(AsynchronousTask<void>* errorCallback) noexcept {
		this->errorCallback = errorCallback;
	}
};


#endif /* SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_ */
