#ifndef SRC_UTILITIES_COMMUNICATION_SERIALRXTX_HPP_
#define SRC_UTILITIES_COMMUNICATION_SERIALRXTX_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include "../streaming/Stream.hpp"
#include <avr/pgmspace.h>


class SerialRxTx {

public:

	Usart& usart; //Todo find better way to expose necessary functionality for reading...

private:

	union TxData {
		const char* string;
		char hex8_pt2;
		Stream<uint8_t>* stream;
		TxData() noexcept : string(nullptr) {}
	} txData;

	enum TxStatus : int8_t {
		DISABLED = -1,
		IDLE = 0,
		COMPLETING = 1,
		TX_STREAM = 2,
		TX_8HEX = 3,
		TX_STRING = 4,
		TX_PROGMEM_STRING = 5
	} volatile txStatus;


	inline void txCompleteCallback() noexcept {
		this->txStatus = TxStatus::IDLE;
	}

	inline void txReadyCallback() noexcept {
		if (this->txStatus == TX_STREAM) {
			if (this->txData.stream->hasNextStreamToken()) {
				usart.write(this->txData.stream->getNextStreamToken());
				return;
			}
		}
		else if (this->txStatus == TX_8HEX) {
			usart.write(this->txData.hex8_pt2);
		}
		else if (this->txStatus == TX_STRING) {
			if (*(++(this->txData.string)) != 0) {
				usart.write(*(this->txData.string));
				return;
			}
		}
		else if (this->txStatus == TX_PROGMEM_STRING) {
			if (pgm_read_byte(++(this->txData.string)) != 0) {
				usart.write(pgm_read_byte(this->txData.string));
				return;
			}
		}
		this->txStatus = TxStatus::COMPLETING;
		this->usart.disableDataRegisterEmptyInterrupt();
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
			: usart(usart), txData(), txStatus(TxStatus::DISABLED) {
		txIrq.registerMethod<SerialRxTx, &SerialRxTx::txCompleteCallback>(*this);
		udreIrq.registerMethod<SerialRxTx, &SerialRxTx::txReadyCallback>(*this);
	}

	inline void init() noexcept { usart.init(); }
	inline void close() noexcept { usart.close(); }

	inline void configureAsync(Usart::UCSRC::FIELDS::ParityModeUPM parity, Usart::UCSRC::FIELDS::StopBitsUSBS stopBits, uint16_t baudRateRegisterValue, bool doubleSpeed = false) noexcept {
		this->usart.setUartMode(Usart::UCSRC::FIELDS::UsartModeUMSEL::ASYNC);
		this->usart.setCharacterSize(8);
		this->usart.setParityMode(parity);
		this->usart.setStopBits(stopBits);
		this->usart.setBaudrateRegisterValue(baudRateRegisterValue);
		if (doubleSpeed) {
			this->usart.enableDoubleAsyncSpeed();
		}
		else {
			this->usart.disableDoubleAsyncSpeed();
		}
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

	inline bool transmit(char character, bool synchronous = false) noexcept {
		if (this->txStatus == TxStatus::IDLE) {
			this->txStatus = TxStatus::COMPLETING;
			this->usart.write(character);
			if(synchronous) {
				while(!this->isReadyToTransmit());
			}
			return true;
		}
		else {
			return false;
		}
	}

	inline bool transmit(const char* s, bool synchronous = false) noexcept {
		if (*s != 0) {
			if (this->txStatus == TxStatus::IDLE) {
				this->txStatus = TxStatus::TX_STRING;
				this->txData.string = s;
				usart.write(*s);
				this->usart.enableDataRegisterEmptyInterrupt();
				if(synchronous) {
					while(!this->isReadyToTransmit());
				}
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

	inline bool transmitFromProgmem(PGM_P s, bool synchronous = false) noexcept {
		if (*s != 0) {
			if (this->txStatus == TxStatus::IDLE) {
				this->txStatus = TxStatus::TX_PROGMEM_STRING;
				this->txData.string = s;
				usart.write(pgm_read_byte(s));
				this->usart.enableDataRegisterEmptyInterrupt();
				if(synchronous) {
					while(!this->isReadyToTransmit());
				}
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

	inline bool transmit(Stream<uint8_t>* stream, bool synchronous = false) {
		if (stream->hasNextStreamToken()) {
			if (this->txStatus == TxStatus::IDLE) {
				this->txStatus = TxStatus::TX_STREAM;
				this->txData.stream = stream;
				usart.write(stream->getNextStreamToken());
				this->usart.enableDataRegisterEmptyInterrupt();
				if(synchronous) {
					while(!this->isReadyToTransmit());
				}
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

	inline bool transmitHex(uint8_t value, bool synchronous = false) noexcept {
		if (this->txStatus == TxStatus::IDLE) {
			this->txStatus = TxStatus::TX_8HEX;
			uint8_t pt2 = value & 0x0F;
			this->txData.hex8_pt2 = pt2 > 9 ? pt2 + ('A' - 10) : pt2 + '0';
			value = value >> 4; //pt1
			this->usart.write(char(value > 9 ? value + ('A' - 10) : value + '0'));
			this->usart.enableDataRegisterEmptyInterrupt();
			if(synchronous) {
				while(!this->isReadyToTransmit());
			}
			return true;
		}
		else {
			return false;
		}
	}
};


#endif /* SRC_UTILITIES_COMMUNICATION_SERIALRXTX_HPP_ */
