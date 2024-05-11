#ifndef SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_
#define SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include "../scheduling/AsynchronousTask.hpp"


class I2cMaster {

private:
	static constexpr uint8_t NumberOfOperations = 2;

	Twi& twi;

	AsynchronousTask<void>* errorCallback;

	struct Operation {
		enum Type : uint8_t {
			SingleData = 0,
			ArrayData = 1,
			StringData = 2
		} volatile type;
		union Data {
			uint8_t single;
			uint8_t* array;
			const char* string;
		} volatile data;
		volatile uint8_t slaRW;
		volatile uint8_t length; //decrementing counter, 0 when completed
		AsynchronousTask<void>* completionCallback;

		inline void clear() noexcept {
			this->length = 0;
			this->data.array = nullptr;
			this->completionCallback = nullptr;
		}

	} operations[NumberOfOperations];

	volatile uint8_t activeOperation;

	enum Status : int8_t {
		Idle = 0,
		Busy = 1,
		BusError = -1,
		ArbitrationLost = -2,
		AddressNack = -3,
		DataNack = -4,
		TransmissionError = -5
	} volatile status;


	inline void prepareNextOperation() noexcept {
		this->activeOperation = (this->activeOperation + 1) % NumberOfOperations;
		if (this->operations[this->activeOperation].length > 0) { //-> repeated start
			this->twi.scheduleStart();
		}
		else {
			this->twi.stop();
			this->status = Status::Idle;
		}
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
		case Twi::TWSReg::FIELDS::Status::M_RepeatedStartTransmitted:
			this->twi.clearStart();
			this->twi.setData(this->operations[this->activeOperation].slaRW);
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_W_ACK:
		case Twi::TWSReg::FIELDS::Status::M_DataTransmitted_ACK:
			if (this->operations[this->activeOperation].length > 0) {
				switch (this->operations[this->activeOperation].type) {
				case Operation::Type::SingleData:
					this->twi.setData(this->operations[this->activeOperation].data.single);
					this->operations[this->activeOperation].length = 0;
					break;
				case Operation::Type::ArrayData:
					this->twi.setData(*this->operations[this->activeOperation].data.array);
					this->operations[this->activeOperation].data.array++;
					this->operations[this->activeOperation].length--;
					break;
				case Operation::Type::StringData:
					this->twi.setData(*this->operations[this->activeOperation].data.string);
					if (*this->operations[this->activeOperation].data.string == 0) {
						this->operations[this->activeOperation].length = 0;
					}
					this->operations[this->activeOperation].data.string++;
					break;
				}
				this->twi.clearInterruptFlag();
			}
			else {
				this->operations[this->activeOperation].clear();
				if (this->operations[this->activeOperation].completionCallback != nullptr) {
					this->operations[this->activeOperation].completionCallback->execute<REPEATEDLY>();
				}
				this->prepareNextOperation();
			}
			break;
		case Twi::TWSReg::FIELDS::Status::M_SLA_R_ACK:
			this->twi.clearInterruptFlag();
			break;
		case Twi::TWSReg::FIELDS::Status::M_DataReceived_ACK:
			switch (this->operations[this->activeOperation].type) {
			case Operation::Type::SingleData:
			case Operation::Type::ArrayData:
				*this->operations[this->activeOperation].data.array = twi.readData();
				this->operations[this->activeOperation].length--;
				if (this->operations[this->activeOperation].length > 0) {
					this->operations[this->activeOperation].data.array++;
				}
				break;
			case Operation::Type::StringData:
				*this->operations[this->activeOperation].data.string = twi.readData();
				if (*this->operations[this->activeOperation].data.string == 0) {
					this->operations[this->activeOperation].length = 0;
				}
				else {
					this->operations[this->activeOperation].length--;
					this->operations[this->activeOperation].data.string++;
				}
			}
			if (this->operations[this->activeOperation].length == 0) {
				this->operations[this->activeOperation].clear();
				if (this->operations[this->activeOperation].completionCallback != nullptr) {
					this->operations[this->activeOperation].completionCallback->execute<REPEATEDLY>();
				}
				this->prepareNextOperation();
			}
			else {
				this->twi.clearInterruptFlag();
			}
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

	inline I2cMaster(Twi& twi, Interrupt twiIrq) noexcept: twi(twi), errorCallback(nullptr), operations({}), activeOperation(0), status(Status::Idle) {
		for (uint8_t i = 0; i < NumberOfOperations; i++) {
			this->operations[i].clear();
		}
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

	inline bool writeAsync(uint8_t address, uint8_t data, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (this->status == Status::Idle) {
			this->operations[this->activeOperation].slaRW = (address << 1);
			this->operations[this->activeOperation].data.single = data;
			this->operations[this->activeOperation].type = Operation::Type::SingleData;
			this->operations[this->activeOperation].length = 1;
			this->operations[this->activeOperation].completionCallback = completionCallback;
			this->status = Status::Busy;
			this->twi.scheduleStart();
			this->twi.clearInterruptFlag();
			return true;
		}
		else if (this->status == Status::Busy) {
			uint8_t nextOperation = (this->activeOperation + 1) % NumberOfOperations;
			if (this->operations[nextOperation].length > 0) {
				return false;
			}
			else  {
				this->operations[nextOperation].length = 1;
				this->operations[nextOperation].slaRW = (address << 1);
				this->operations[nextOperation].type = Operation::Type::SingleData;
				this->operations[nextOperation].data.single = data;
				this->operations[this->activeOperation].completionCallback = completionCallback;
				return true;
			}
		}
		else {
			return false;
		}
	}

	inline bool writeAsync(uint8_t address, uint8_t* data, uint8_t length, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (length > 0) {
			if (this->status == Status::Idle) {
				this->operations[this->activeOperation].slaRW = (address << 1);
				this->operations[this->activeOperation].data.array = data;
				this->operations[this->activeOperation].type = Operation::Type::ArrayData;
				this->operations[this->activeOperation].length = length;
				this->operations[this->activeOperation].completionCallback = completionCallback;
				this->status = Status::Busy;
				this->twi.scheduleStart();
				this->twi.clearInterruptFlag();
				return true;
			}
			else if (this->status == Status::Busy) {
				uint8_t nextOperation = (this->activeOperation + 1) % NumberOfOperations;
				if (this->operations[nextOperation].length > 0) {
					return false;
				}
				else  {
					this->operations[nextOperation].length = length;
					this->operations[nextOperation].slaRW = (address << 1);
					this->operations[nextOperation].data.array = data;
					this->operations[nextOperation].type = Operation::Type::ArrayData;
					this->operations[this->activeOperation].completionCallback = completionCallback;
					return true;
				}
			}
		}
		return false;
	}

	inline bool writeAsync(uint8_t address, const char* string, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (this->status == Status::Idle) {
			this->operations[this->activeOperation].slaRW = (address << 1);
			this->operations[this->activeOperation].data.string = string;
			this->operations[this->activeOperation].type = Operation::Type::StringData;
			this->operations[this->activeOperation].length = 1;
			this->operations[this->activeOperation].completionCallback = completionCallback;
			this->status = Status::Busy;
			this->twi.scheduleStart();
			this->twi.clearInterruptFlag();
			return true;
		}
		else if (this->status == Status::Busy) {
			uint8_t nextOperation = (this->activeOperation + 1) % NumberOfOperations;
			if (this->operations[nextOperation].length > 0) {
				return false;
			}
			else  {
				this->operations[nextOperation].length = 1;
				this->operations[nextOperation].slaRW = (address << 1);
				this->operations[nextOperation].data.string = string;
				this->operations[nextOperation].type = Operation::Type::StringData;
				this->operations[this->activeOperation].completionCallback = completionCallback;
				return true;
			}
		}
		else {
			return false;
		}
	}

	inline bool readAsync(uint8_t address, uint8_t* buffer, uint8_t buffersize = 1, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (buffersize > 0) {
			if (this->status == Status::Idle) {
				this->operations[this->activeOperation].slaRW = ((address << 1) | 0x01);
				this->operations[this->activeOperation].data.array = buffer;
				this->operations[this->activeOperation].type = Operation::Type::ArrayData;
				this->operations[this->activeOperation].length = buffersize;
				this->operations[this->activeOperation].completionCallback = completionCallback;
				this->status = Status::Busy;
				this->twi.scheduleStart();
				this->twi.clearInterruptFlag();
				return true;
			}
			else if (this->status == Status::Busy) {
				uint8_t nextOperation = (this->activeOperation + 1) % NumberOfOperations;
				if (this->operations[nextOperation].length > 0) {
					return false;
				}
				else  {
					this->operations[nextOperation].length = buffersize;
					this->operations[nextOperation].slaRW = ((address << 1) | 0x01);
					this->operations[nextOperation].type = Operation::Type::ArrayData;
					this->operations[nextOperation].data.array = buffer;
					this->operations[this->activeOperation].completionCallback = completionCallback;
					return true;
				}
			}
		}
		return false;
	}

	inline bool readAsync(uint8_t address, const char* buffer, uint8_t buffersize, AsynchronousTask<void>* completionCallback = nullptr) noexcept {
		if (buffersize > 0) {
			if (this->status == Status::Idle) {
				this->operations[this->activeOperation].slaRW = ((address << 1) | 0x01);
				this->operations[this->activeOperation].data.string = buffer;
				this->operations[this->activeOperation].type = Operation::Type::StringData;
				this->operations[this->activeOperation].length = buffersize;
				this->operations[this->activeOperation].completionCallback = completionCallback;
				this->status = Status::Busy;
				this->twi.scheduleStart();
				this->twi.clearInterruptFlag();
				return true;
			}
			else if (this->status == Status::Busy) {
				uint8_t nextOperation = (this->activeOperation + 1) % NumberOfOperations;
				if (this->operations[nextOperation].length > 0) {
					return false;
				}
				else  {
					this->operations[nextOperation].length = buffersize;
					this->operations[nextOperation].slaRW = ((address << 1) | 0x01);
					this->operations[nextOperation].type = Operation::Type::StringData;
					this->operations[nextOperation].data.string = buffer;
					this->operations[this->activeOperation].completionCallback = completionCallback;
					return true;
				}
			}
		}
		return false;
	}

	inline uint8_t readSync(uint8_t address) noexcept {
		uint8_t buffer;
		struct Semaphore {
			volatile bool wait = true;
			inline void resume() noexcept { this->wait = false; }
		} semaphore;
		AsynchronousTask<void> completedCallback = AsynchronousTask<void>();
		completedCallback.scheduleMethod<Semaphore, &Semaphore::resume>(semaphore);
		if (!readAsync(address, &buffer, 1, &completedCallback)) {
			return 0;
		}
		while (semaphore.wait) {
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
		this->status = Status::Idle;
		for (uint8_t i = 0; i < NumberOfOperations; i++) {
			this->operations[i].clear();
		}
		this->twi.stop(); //TransmissionError recovery
		this->twi.clearInterruptFlag();

	}

	inline void setErrorCallback(AsynchronousTask<void>* errorCallback) noexcept {
		this->errorCallback = errorCallback;
	}

};


#endif /* SRC_UTILITIES_COMMUNICATION_I2CMASTER_HPP_ */
