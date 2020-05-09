#ifndef SRC_RESOURCES_PERIPHERY_USART_H_
#define SRC_RESOURCES_PERIPHERY_USART_H_


#include <stdint.h>
#include "../Periphery.h"
#include <util/atomic.h>

#include "../Interrupts.h"


///MMIO Abstraction of the USARTs
class Usart final {

private:

	///Allocation Flags for all Usarts TODO: Inhibit when Periphery::runtimeAllocationsEnabled==false
	static uint8_t usage;

	///No Constructor to prohibit instantiation
	Usart() = delete;

public:

	///The UCSRnA register
	volatile union unionUCSRA {
		volatile struct structUCSRA {
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
	volatile struct UCSRB {
		volatile uint8_t dataTXB8 : 1; //Transmit Data Bit 8
		volatile const uint8_t dataRXB8 : 1; //Receive Data Bit 8
		volatile uint8_t flagUCSZ2 : 1; //Character size (Bit 2)
		volatile uint8_t flagTXEN : 1; //Transmitter enable
		volatile uint8_t flagRXEN : 1; //Receiver enable
		volatile uint8_t flagUDRIE : 1; //Data-Register-Empty Interrupt enable
		volatile uint8_t flagTXCIE : 1; //TX-Complete Interrupt enable
		volatile uint8_t flagRXCIE : 1; //RX-Complete Interrupt enable
	} regUCSRB;

	///The UCSRnC register
	volatile struct UCSRC {
		volatile uint8_t flagUCPOL : 1; //Clock Polarity
		volatile uint8_t dataUCSZ : 2; //Character size (Bit 0-1)
		volatile uint8_t flagUSBS : 1; //Stop bit select
		volatile uint8_t dataUPM : 2; //Parity Mode
		volatile uint8_t dataUMSEL : 2; //Usart Mode select
	} regUCSRC;

private:

	///unused register
	volatile const uint8_t reserved;

public:

	///The UBRRn register
	volatile uint16_t regUBRR; //baud (H+L)

	///The UDRn register
	volatile uint8_t regUDR; //data

	///Enumeration to describe the basic mode of operation
	enum UsartMode : uint8_t {
		ASYNC = 0x00,
		SYNC = 0x01,
		MASTERSPI = 0x03
	};

	///Enumeration to describe the parity-check mode
	enum ParityMode : uint8_t {
		DISABLED = 0x00,
		EVEN = 0x02,
		ODD = 0x03
	};

	///Enumeration to describe the number of stopbits
	enum StopBits : uint8_t {
		ONE = 0x00,
		TWO = 0x01
	};

	///Enumeration to describe the clock polarity
	enum ClockPolarity : uint8_t {
		RISING = 0x00,
		FALLING = 0x01
	};

	///Initializes the Usart
	inline void init() {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				if (usage & (1 << index)) {
					usage |= (1 << index);
				}
				else {
					//Todo: throw later (check possible problems with throwing in atomic block)
				}
			}
		}
	}

	///De-Initializes the Usart
	inline void close() noexcept {
		if (Periphery::runtimeAllocationsEnabled) {
			uint8_t index = Periphery::getIdentity(this);
			usage &= ~(1 << index);
		}
	}

	///checks the usage of the Usart
	///\return true if it is already in use, else false
	inline bool isUsed() noexcept {
		uint8_t index = Periphery::getIdentity(this);
		return usage & (1 << index);
	}

	inline EventSource& accessRxInterruptSource() noexcept {
		static Interrupt irq = Interrupt::Instantiate<USART0_RX_vect_num>();
		return irq; //TODO: return correct instance for this identity
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_USART_H_ */
