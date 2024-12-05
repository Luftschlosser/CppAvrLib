#include "SerialRxTx.hpp"

bool SerialRxTx::transmit(char character) noexcept {
	if (this->txStatus == TxStatus::IDLE) {
		this->txStatus = TxStatus::COMPLETING;
		this->usart.write(character);
		return true;
	}
	else {
		return false;
	}
}

bool SerialRxTx::transmit(const char* s) noexcept {
	if (*s != 0) {
		if (this->txStatus == TxStatus::IDLE) {
			this->txStatus = TxStatus::TX_STRING;
			this->txData.string = s;
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

bool SerialRxTx::transmitFromProgmem(PGM_P s) noexcept {
	if (pgm_read_byte(s) != 0) {
		if (this->txStatus == TxStatus::IDLE) {
			this->txStatus = TxStatus::TX_PROGMEM_STRING;
			this->txData.pgmString = s;
			usart.write(pgm_read_byte(s));
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

bool SerialRxTx::transmit(Stream<uint8_t>* stream) noexcept {
	if (stream->hasNextStreamToken()) {
		if (this->txStatus == TxStatus::IDLE) {
			this->txStatus = TxStatus::TX_STREAM;
			this->txData.stream = stream;
			usart.write(stream->getNextStreamToken());
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

bool SerialRxTx::transmitHex(uint8_t value) noexcept {
	if (this->txStatus == TxStatus::IDLE) {
		this->txStatus = TxStatus::TX_8HEX;
		uint8_t pt2 = value & 0x0F;
		this->txData.hex8_pt2 = pt2 > 9 ? pt2 + ('A' - 10) : pt2 + '0';
		value = value >> 4; //pt1
		this->usart.write(char(value > 9 ? value + ('A' - 10) : value + '0'));
		this->usart.enableDataRegisterEmptyInterrupt();
		return true;
	}
	else {
		return false;
	}
}

bool SerialRxTx::transmitDec(uint8_t value) noexcept {
	if (this->txStatus == TxStatus::IDLE) {
		this->txStatus = TxStatus::TX_8DEC;
		char buf[3];
		int8_t i;
		for (i = 0; i < 3; i++) {
			buf[i] = (value % 10) + '0';
			value /= 10;
		}
		i = 2;
		while (true) {
			if (buf[i] > '0' || i == 0) {
				this->usart.write(buf[i]);
				break;
			}
			i--;
		}
		this->txData.decPt2[0] = i >= 2 ? buf[1] : 0;
		this->txData.decPt2[1] = i >= 1 ? buf[0] : 0;
		this->usart.enableDataRegisterEmptyInterrupt();
		return true;
	}
	else {
		return false;
	}
}
