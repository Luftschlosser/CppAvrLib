#ifndef SRC_RESOURCES_PERIPHERY_USART_H_
#define SRC_RESOURCES_PERIPHERY_USART_H_


#include <stdint.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


//TODO: allocate Pins when used by USART!
//TODO: add 'getExternalClockInputPin!-method (XCKn Pins)


///MMIO Abstraction of the USARTs
class Usart final {

private:

	///No Constructor to prohibit instantiation
	Usart() = delete;

public:

	///The UCSRnA register
	union UCSRA {
		struct FIELDS {
			volatile uint8_t flagMPCM : 1; //Multi-Processor communication Mode
			volatile uint8_t flagU2X : 1; //Double async transmission speed
			volatile const uint8_t  flagUPE : 1; //Parity Error
			volatile const uint8_t flagDOR : 1; //Data Overrun
			volatile const uint8_t flagFE : 1; //Frame Error
			volatile const uint8_t flagUDRE : 1; //Data Register empty Flag
			volatile uint8_t flagTXC : 1; //Transmit complete Flag
			volatile const uint8_t flagRXC : 1; //Receive complete Flag
		} fields;
		volatile uint8_t reg;
	} regUCSRA;

	///The UCSRnB register
	union UCSRB {
		struct FIELDS {
			volatile uint8_t flagTXB8 : 1; //Transmit Data Bit 8
			volatile const uint8_t flagRXB8 : 1; //Receive Data Bit 8
			volatile uint8_t flagUCSZ2 : 1; //Character size (Bit 2)
			volatile uint8_t flagTXEN : 1; //Transmitter enable
			volatile uint8_t flagRXEN : 1; //Receiver enable
			volatile uint8_t flagUDRIE : 1; //Data-Register-Empty Interrupt enable
			volatile uint8_t flagTXCIE : 1; //TX-Complete Interrupt enable
			volatile uint8_t flagRXCIE : 1; //RX-Complete Interrupt enable
		} fields;
		volatile uint8_t reg;
	} regUCSRB;

	///The UCSRnC register
	union UCSRC {
		struct FIELDS {
			volatile uint8_t flagUCPOL : 1; //Clock Polarity
			volatile uint8_t dataUCSZ : 2; //Character size (Bit 0-1)
			volatile uint8_t flagUSBS : 1; //Stop bit select
			volatile uint8_t dataUPM : 2; //Parity Mode
			volatile uint8_t dataUMSEL : 2; //Usart Mode select

			///Enumeration to describe the clock polarity
			enum ClockPolarityUCPOL : uint8_t {
				RISING = 0x00,
				FALLING = 0x01
			};

			///Enumeration to describe the number of stopbits
			enum StopBitsUSBS : uint8_t {
				ONE = 0x00,
				TWO = 0x01
			};

			///Enumeration to describe the parity-check mode
			enum ParityModeUPM : uint8_t {
				DISABLED = 0x00,
				EVEN = 0x02,
				ODD = 0x03
			};

			///Enumeration to describe the basic mode of operation
			enum UsartModeUMSEL : uint8_t {
				ASYNC = 0x00,
				SYNC = 0x01,
				MASTERSPI = 0x03
			};
		} fields;
		volatile uint8_t reg;
	}
	regUCSRC;

private:

	///unused register
	volatile const uint8_t reserved;

public:

	///The UBRRn register
	volatile uint16_t regUBRR; //baud (H+L)

	///The UDRn register
	volatile uint8_t regUDR; //data


	static constexpr inline uint8_t compileUCSRC(UCSRC::FIELDS::ClockPolarityUCPOL clockPolarity,
			UCSRC::FIELDS::StopBitsUSBS stopBits, UCSRC::FIELDS::ParityModeUPM parityMode,
			UCSRC::FIELDS::UsartModeUMSEL usartMode, uint8_t characterSize) noexcept {
		uint8_t buf = uint8_t(clockPolarity);
		characterSize -= 5;
		if (characterSize >= 4) {
			characterSize = 3;
		}
		buf |= (characterSize << 1);
		buf |= (stopBits << 3);
		buf |= (parityMode << 4);
		buf |= (usartMode << 6);
		return buf;
	}


	///Initializes the Usart
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the Usart
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the Usart
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}


	///Checks if there is unread data in the receive buffer
	inline bool isReceiveComplete() noexcept { return this->regUCSRA.fields.flagRXC == 1; }

	///Checks if the transmit is completed (shift register emptied and no new data in transmit buffer)
	inline bool isTransmitComplete() noexcept { return this->regUCSRA.fields.flagTXC == 1; }

	///Clears the transmit-complete flag
	inline void clearTransmitComplete() noexcept { this->regUCSRA.fields.flagTXC = 1; }

	///Checks if the data register (transmit buffer) is empty and ready to receive new data
	inline bool isDataRegisterEmpty() noexcept { return this->regUCSRA.fields.flagUDRE == 1; }

	///Checks if ANY error occured (Frame error / Data overrun error / Parity error)
	inline bool hasError() noexcept { return this->regUCSRA.reg & 0x1C; /*mask 0b00011100*/ }

	///Checks if a Frame Error occured
	inline bool hasFrameError() noexcept { return this->regUCSRA.fields.flagFE == 1; }

	///Checks if a Data OverRun Error occured
	inline bool hasDataOverRunError() noexcept { return this->regUCSRA.fields.flagDOR == 1; }

	///Checks if a Parity Error occured
	inline bool hasParityError() noexcept { return this->regUCSRA.fields.flagUPE == 1; }

	///Doubles the transmission speed in Async-Mode
	inline void enableDoubleAsyncSpeed() noexcept { this->regUCSRA.fields.flagU2X = 1; }

	///Resets the transmission speed in Async-Mode to normal (not double)
	inline void disableDoubleAsyncSpeed() noexcept { this->regUCSRA.fields.flagU2X = 0; }

	///Enable Multi-Processor Communciation Mode
	inline void enableMultiProcessorCommunicationMode() noexcept { this->regUCSRA.fields.flagMPCM = 1; }

	///Disable Multi-Processor Communciation Mode
	inline void disableMultiProcessorCommunicationMode() noexcept { this->regUCSRA.fields.flagMPCM = 0; }

	///Enables the RX-Complete Interrupt
	inline void enableRXCompleteInterrupt() noexcept { this->regUCSRB.fields.flagRXCIE = 1; }

	///Disables the RX-Complete Interrupt
	inline void disableRXCompleteInterrupt() noexcept { this->regUCSRB.fields.flagRXCIE = 0; }

	///Enables the TX-Complete Interrupt
	inline void enableTXCompleteInterrupt() noexcept { this->regUCSRB.fields.flagTXCIE = 1; }

	///Disables the TX-Complete Interrupt
	inline void disableTXCompleteInterrupt() noexcept { this->regUCSRB.fields.flagTXCIE = 0; }

	///Enables the Data-Register-Empty Interrupt
	inline void enableDataRegisterEmptyInterrupt() noexcept { this->regUCSRB.fields.flagUDRIE = 1; }

	///Disables the Data-Register-Empty Interrupt
	inline void disableDataRegisterEmptyInterrupt() noexcept { this->regUCSRB.fields.flagUDRIE = 0; }

	///Enables the Receiver
	inline void enableReceiver() noexcept { this->regUCSRB.fields.flagRXEN = 1; } //TODO: AutoPinAllocation

	///Disables the Receiver
	inline void disableReceiver() noexcept { this->regUCSRB.fields.flagRXEN = 0; } //TODO: AutoPinAllocation

	///Enables the Transmitter
	inline void enableTransmitter() noexcept { this->regUCSRB.fields.flagTXEN = 1; } //TODO: AutoPinAllocation

	///Disables the Transmitter
	inline void disableTransmitter() noexcept { this->regUCSRB.fields.flagTXEN = 0; } //TODO: AutoPinAllocation

	///Reads the ninth data bit
	inline bool getNinthDataBit() noexcept { return this->regUCSRB.fields.flagRXB8 == 1; }

	///Writes the ninth data bit
	inline void setNinthDataBit(bool data) noexcept { data ? this->regUCSRB.fields.flagTXB8 = 1 : this->regUCSRB.fields.flagTXB8 = 0; }

	///Sets the Mode of Operation [ ASYNC / SYNC / MASTERSPI ]
	inline void setUartMode(UCSRC::FIELDS::UsartModeUMSEL mode) noexcept { this->regUCSRC.fields.dataUMSEL = mode; }

	///Sets the Parity Mode [ DISABLED / EVEN / ODD ]
	inline void setParityMode(UCSRC::FIELDS::ParityModeUPM mode) noexcept { this->regUCSRC.fields.dataUPM = mode; }

	///Sets the number of Stopbits [ ONE / TWO ]
	inline void setStopBits(UCSRC::FIELDS::StopBitsUSBS mode) noexcept { this->regUCSRC.fields.flagUSBS = mode; }

	///Sets the character size [5-9]
	inline void setCharacterSize(const uint8_t size) noexcept { //TODO: change to safe template-version
		if (size >= 5 && size <= 8) {
			this->regUCSRB.fields.flagUCSZ2 = 0;
			this->regUCSRC.fields.dataUCSZ = size - 5;
		}
		else if (size == 9) {
			this->regUCSRC.fields.dataUCSZ = 0x3;
			this->regUCSRB.fields.flagUCSZ2 = 1;
		}
	}

	///Sets the clock polarity [ RISING / FALLING ]
	inline void setClockPolarity(UCSRC::FIELDS::ClockPolarityUCPOL mode) noexcept { this->regUCSRC.fields.flagUCPOL = mode; }

	///Sets the baudrate
	inline void setBaudrateRegisterValue(uint16_t baudrate) noexcept { this->regUBRR = baudrate; }

	///Read the data in the receive buffer (first 8 Bits, use "getNinthDataBit()" for the ninth Bit)
	inline char read() noexcept { return this->regUDR; }

	///Write data to the transmit buffer (first 8 Bits, use "setNinthDataBit()" for the ninth Bit)
	inline void write(char data) noexcept { this->regUDR = data; }

	///Write data to the transmit buffer (first 8 Bits, use "setNinthDataBit()" for the ninth Bit)
	inline void write(uint8_t data) noexcept { this->regUDR = data; }

	///Writes data to the transmit buffer (up to nine Bits)
	inline void write(uint16_t data) noexcept { //TODO: Check if atomic block is necessary?
		uint8_t first = data;
		uint8_t last = data >> 8;
		this->regUDR = first;
		if (last & 0x1) {
			this->regUCSRB.fields.flagTXB8 = 1;
		}
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_USART_H_ */
