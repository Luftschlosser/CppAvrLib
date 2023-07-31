#ifndef SRC_UTILITIES_COMMUNICATION_SERIALRXTX_HPP_
#define SRC_UTILITIES_COMMUNICATION_SERIALRXTX_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"


class SerialRxTx {

public:

	Usart& usart;

private:

	const char* txData;

	enum TxStatus : int8_t {
		DISABLED = -1,
		IDLE = 0,
		COMPLETING = 1,
		TX_STRING = 2
	} volatile txStatus;


	inline void txCompleteCallback() noexcept {
		this->txStatus = TxStatus::IDLE;
	}

	inline void txReadyCallback() noexcept {
		if (this->txStatus == TX_STRING) {
			if (*(++(this->txData)) != 0) {
				usart.write(*(this->txData));
			}
			else {
				this->txStatus = TxStatus::COMPLETING;
				this->usart.disableDataRegisterEmptyInterrupt();
			}
		}
	}

public:

	///Enumeration to describe different kinds of Receive-Error which can occur
	enum RxErrorType : uint8_t {
		NONE = 0,
		DATA_OVERRUN,
		PARITY_ERROR,
		FRAME_ERROR
	};


	inline SerialRxTx(Usart& usart, Interrupt txIrq, Interrupt udreIrq) noexcept
			: usart(usart), txData(nullptr), txStatus(TxStatus::DISABLED) {
		txIrq.registerMethod<SerialRxTx, &SerialRxTx::txCompleteCallback>(*this);
		udreIrq.registerMethod<SerialRxTx, &SerialRxTx::txReadyCallback>(*this);
	}

	inline void init() noexcept { usart.init(); }
	inline void close() noexcept { usart.close(); }

	inline void configureAsync(Usart::UCSRC::FIELDS::ParityModeUPM parity, Usart::UCSRC::FIELDS::StopBitsUSBS stopBits, uint16_t baudRateRegisterValue) noexcept {
		this->usart.setUartMode(Usart::UCSRC::FIELDS::UsartModeUMSEL::ASYNC);
		this->usart.setCharacterSize(8);
		this->usart.setParityMode(parity);
		this->usart.setStopBits(stopBits);
		this->usart.setBaudrateRegisterValue(baudRateRegisterValue);
	}

	inline void configureSync(Usart::UCSRC::FIELDS::ClockPolarityUCPOL clkPolarity, Usart::UCSRC::FIELDS::ParityModeUPM parity, Usart::UCSRC::FIELDS::StopBitsUSBS stopBits, uint16_t baudRateRegisterValue) noexcept {
		this->usart.setUartMode(Usart::UCSRC::FIELDS::UsartModeUMSEL::SYNC);
		this->usart.setCharacterSize(8);
		this->usart.setClockPolarity(clkPolarity);
		this->usart.setParityMode(parity);
		this->usart.setStopBits(stopBits);
		this->usart.setBaudrateRegisterValue(baudRateRegisterValue);
	}

	inline void enableReceiver() noexcept {
		this->usart.enableRXCompleteInterrupt();
		this->usart.enableReceiver();
	}

	inline void disableReceiver() noexcept {
		this->usart.disableReceiver();
		this->usart.disableRXCompleteInterrupt();
	}

	inline RxErrorType getReceiverErrorStatus() noexcept {
		if (!this->usart.hasError()) {
			return NONE;
		}
		else if (this->usart.hasDataOverRunError()) {
			return DATA_OVERRUN;
		}
		else if (this->usart.hasFrameError()) {
			return FRAME_ERROR;
		}
		else if (this->usart.hasParityError()) {
			return PARITY_ERROR;
		}
		else {
			return NONE;
		}
	}

	inline void enableTransmitter() noexcept {
		this->usart.clearTransmitComplete();
		this->usart.enableTXCompleteInterrupt();
		this->usart.enableTransmitter();
		this->txStatus = TxStatus::IDLE;
	}

	inline void disableTransmitter() noexcept {
		this->usart.disableTransmitter();
		this->usart.disableTXCompleteInterrupt();
		this->txStatus = TxStatus::DISABLED;
	}

	inline bool isReadyToTransmit() const noexcept {
		return this->txStatus == TxStatus::IDLE;
	}

	inline bool transmit(char character) noexcept {
		if (this->txStatus == TxStatus::IDLE) {
			this->txStatus = TxStatus::COMPLETING;
			this->usart.write(character);
			return true;
		}
		else {
			return false;
		}
	}

	inline bool transmit(const char* s) noexcept {
		if (*s != 0) {
			if (this->txStatus == TxStatus::IDLE) {
				this->txStatus = TxStatus::TX_STRING;
				this->txData = s;
				usart.write(*s);
				this->usart.enableDataRegisterEmptyInterrupt();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
};


#endif /* SRC_UTILITIES_COMMUNICATION_SERIALRXTX_HPP_ */
