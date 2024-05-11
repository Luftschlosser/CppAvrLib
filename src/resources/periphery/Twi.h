#ifndef SRC_RESOURCES_PERIPHERY_TWI_H_
#define SRC_RESOURCES_PERIPHERY_TWI_H_


#include <stdint.h>
#include "../Configuration.h"
#include "utilities/RuntimeAllocator.h"


//Forward Declarations
namespace Periphery {
	inline Pin getTwiSclPin() noexcept;
	inline Pin getTwiSdaPin() noexcept;
}


///MMIO Abstraction of the TWIs
class Twi final {

private:

	///No Constructor to prohibit instantiation
	Twi() = delete;

public:

	/// The TWI Bit Rate Register
	volatile uint8_t regTWBR;

	///The TWI Status Register
	union TWSReg {
		struct FIELDS {
			volatile const uint8_t dataTWS : 5; //TWI Status
			volatile const uint8_t reserved : 1;
			volatile uint8_t dataTWPS : 2; //TWI Prescaler Bits

			//Enumeration for interpreting the Status-Bytes
			enum Status : uint8_t {
				BusError = 0x00 >> 3,
				M_StartTransmitted = 0x08 >> 3,
				M_RepeatedStartTransmitted = 0x10 >> 3,
				M_SLA_W_ACK = 0x18 >> 3,
				M_SLA_W_NACK = 0x20 >> 3,
				M_DataTransmitted_ACK = 0x28 >> 3,
				M_DataTransmitted_NACK = 0x30 >> 3,
				M_ArbitrationLost = 0x38 >> 3,
				M_SLA_R_ACK = 0x40 >> 3,
				M_SLA_R_NACK = 0x48 >> 3,
				M_DataReceived_ACK = 0x50 >> 3,
				M_DataReceived_NACK = 0x58 >> 3,
				S_SLA_W_ACK = 0x60 >> 3,
				M_ArbitrationLost_SLA_W = 0x68 >> 3,
				S_Broadcast_ACK = 0x70,
				M_ArbitrationLost_Broadcast = 0x78 >> 3,
				S_DataReceived_ACK = 0x80 >> 3,
				S_DataReceived_NACK = 0x88 >> 3,
				S_DataBroadcastReceived_ACK = 0x90 >> 3,
				S_DataBroadcastReceived_NACK = 0x98 >> 3,
				S_StopReceived = 0xA0 >> 3,
				S_SLA_R_ACK = 0xA8 >> 3,
				M_ArbitrationLost_SLA_R = 0xB0 >> 3,
				S_DataTransmitted_ACK = 0xB8 >> 3,
				S_DataTransmitted_NACK = 0xC0 >> 3,
				S_TransmitStopped_ACK = 0xC8 >> 3,
				Idle = 0xF8 >> 3
			};

			//Enumeration for the Prescaler Values
			enum Prescaler : uint8_t {
				Prescale_1 = 0x00,
				Prescale_4 = 0x01,
				Prescale_16 = 0x02,
				Prescale_64 = 0x03
			};

		} fields;
		volatile uint8_t reg;
	} regTWSR;

	///The TWI (Slave) Address Register
	union TWAReg {
		struct FIELDS {
			volatile uint8_t dataTWA : 7; //TWI (Slave) Address
			volatile uint8_t flagTWGCE : 1; //TWI General Call Recognition Enable Bit
		} fields;
		volatile uint8_t reg;
	} regTWAR;

	///The TWI Data Register
	volatile uint8_t regTWDR;

	///The TWI Control Register
	union TWCReg {
		struct FIELDS {
			volatile uint8_t flagTWINT : 1; //TWI Interrupt Flag
			volatile uint8_t flagTWEA : 1; //TWI Enable Acknowledge Bit
			volatile uint8_t  flagTWSTA : 1; //TWI START Condition Bit
			volatile uint8_t flagTWSTO : 1; //TWI STOP Condition Bit
			volatile const uint8_t flagTWWC : 1; //TWI Write Collision Flag
			volatile uint8_t flagTWEN : 1; //TWI Enable Bit
			volatile const uint8_t reserved : 1;
			volatile uint8_t flagTWIE : 1; //TWI Interrupt Enable
		} fields;
		volatile uint8_t reg;
	} regTWCR;

	///The TWI (Slave) Address Mask Register
	union TWAMReg {
		struct FIELDS {
			volatile uint8_t dataTWAM : 7; //TWI Address Mask
			volatile const uint8_t reserved : 1;
		} fields;
		volatile uint8_t reg;
	} regTWAMR;


	///Initializes the TWI
	inline void init() const {
		if (Configuration::runtimeAllocationsEnabled) {
			if (! RuntimeAllocator::allocate(this)) {
				//TODO throw
			}
		}
	}

	///De-Initializes the TWI
	inline void close() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			RuntimeAllocator::deallocate(this);
		}
	}

	///checks the usage of the TWI
	///\return true if it is already in use, else false
	inline bool isUsed() const noexcept {
		if (Configuration::runtimeAllocationsEnabled) {
			return RuntimeAllocator::isAllocated(this);
		}
		else {
			return false;
		}
	}

	///Sets the value of the TWOI Bitrate Register
	///\param bitrate the new bitrate value
	inline void setBitRate(uint8_t bitrate) noexcept {
		this->regTWBR = bitrate;
	}

	///Clears the Interrupt Flag "TWINT" by writing a logic 1 to it. This is used to start the operation of the TWI.
	inline void clearInterruptFlag() noexcept {
		this->regTWCR.fields.flagTWINT = 1;
	}

	///Enables the generation of the Acknowledge pulse
	inline void enableAck() noexcept {
		this->regTWCR.fields.flagTWEA = 1;
	}

	///Disables the generation of the Acknowledge pulse. This can be used to virtually disconnect the device from the TWI bus.
	inline void disableAck() noexcept {
		this->regTWCR.fields.flagTWEA = 0;
	}

	///Become Master of the Bus by transmitting a new Start-Condition asap.
	inline void scheduleStart() noexcept {
		this->regTWCR.fields.flagTWSTA = 1;
	}

	///Necessary to clear the "TWSTA"-flag after successfully becoming the Master of the bus.
	inline void clearStart() noexcept {
		this->regTWCR.fields.flagTWSTA = 0;
	}

	///Generates a Stop-Condition on the bus. Can also be used to recover from an Error condition.
	inline void stop() noexcept {
		this->regTWCR.fields.flagTWSTO = 1;
	}

	///Checks if the write collision flag is set.
	inline bool hasWriteCollision() const noexcept {
		return (this->regTWCR.fields.flagTWWC > 0);
	}

	///Enables the TWI Periphery
	inline void enable() noexcept {
		this->regTWCR.fields.flagTWEN = 1;
		if (Configuration::autoPinAllocationEnabled) {
			Pin sda = Periphery::getTwiSdaPin();
			Pin scl = Periphery::getTwiSclPin();
			sda.init(); //TODO: Deal with possible exception!
			scl.init(); //TODO: Deal with possible exception!
		}
	}

	///Disables the TWI Periphery
	inline void disable() noexcept {
		this->regTWCR.fields.flagTWEN = 0;
		if (Configuration::autoPinAllocationEnabled) {
			Pin sda = Periphery::getTwiSdaPin();
			Pin scl = Periphery::getTwiSclPin();
			sda.close();
			scl.close();
		}
	}

	///Enables the TWI interrupt
	inline void enableInterrupt() noexcept {
		this->regTWCR.fields.flagTWIE = 1;
	}

	///Disables the TWI interrupt
	inline void disableInterrupt() noexcept {
		this->regTWCR.fields.flagTWIE = 0;
	}

	///Returns the TWI-Status
	inline TWSReg::FIELDS::Status getStatus() const noexcept {
		return TWSReg::FIELDS::Status(this->regTWSR.fields.dataTWS);
	}

	///Sets the prescalar value
	inline void setPrescalar(TWSReg::FIELDS::Prescaler prescale) noexcept {
		this->regTWSR.fields.dataTWPS = prescale;
	}

	///Writes Data to transmit into the TWI Data Register
	inline void setData(uint8_t data) noexcept {
		this->regTWDR = data;
	}

	///Reads data from the TWI Data Register
	inline uint8_t readData() const noexcept {
		return this->regTWDR;
	}

	///Sets the slave address of this device
	inline void setSlaveAddress(uint8_t address) noexcept {
		this->regTWAR.fields.dataTWA = (address & 0x7F);
	}

	///Enables the Recognition of general calls
	inline void enableBroadcasts() noexcept {
		this->regTWAR.fields.flagTWGCE = 1;
	}

	///Disables the Recognition of general calls
	inline void disableBroadcasts() noexcept {
		this->regTWAR.fields.flagTWGCE = 0;
	}

	///Sets the Slave Address Mask
	inline void setSlaveAddressMask(uint8_t mask) noexcept {
		this->regTWAMR.reg = (mask & 0xFE);
	}
};

#endif /* SRC_RESOURCES_PERIPHERY_TWI_H_ */
