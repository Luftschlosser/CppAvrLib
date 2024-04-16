#ifndef SRC_UTILITIES_COMMUNICATION_DMXCLIENT_HPP_
#define SRC_UTILITIES_COMMUNICATION_DMXCLIENT_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include "../../utilities/scheduling/AsynchronousTask.hpp"


/* very stupid implementation, doesn't validate anything, uses a lot of memory (saves not only the interesting bits)*/
class DmxClient {

private:
	static constexpr uint16_t Buffersize = 512;
	Usart& usart;
	uint8_t data [2][Buffersize]; //Double-Buffer for safe readout
	volatile uint8_t activeBuffer;
	volatile uint16_t receiveIndex;
	AsynchronousTask<void>* updateCallback;

public:
	inline DmxClient(Usart& usart, Interrupt& rxIrq, AsynchronousTask<void>* updateCallback = nullptr) noexcept
			: usart(usart), data{}, activeBuffer(0), receiveIndex(0), updateCallback(updateCallback) {
		rxIrq.registerMethod<DmxClient, &DmxClient::rxReadyCallback>(*this);
	}

	inline ~DmxClient() noexcept {
		this->disable();
		this->usart.close();
	}

	template <uint32_t FCPU> inline void init() noexcept {
		this->usart.init();
		this->usart.setUartMode(Usart::UCSRC::FIELDS::UsartModeUMSEL::ASYNC);
		this->usart.setCharacterSize(8);
		this->usart.setParityMode(Usart::UCSRC::FIELDS::ParityModeUPM::DISABLED);
		this->usart.setStopBits(Usart::UCSRC::FIELDS::StopBitsUSBS::TWO);
		this->usart.setBaudrateRegisterValue(static_cast<uint16_t>((FCPU / (16 * 250000)) - 1));
		this->data[0][0] = this->data[1][0] = 1; //Make StartByte invalid before receiving any real data
		for (uint16_t i = 1; i < Buffersize; i++) {
			this->data[0][i] = this->data[1][i] = 0;
		}
	}

	inline void enable() noexcept {
		this->usart.enableRXCompleteInterrupt();
		this->usart.enableReceiver();
	}

	inline void disable() noexcept {
		this->usart.disableReceiver();
		this->usart.disableRXCompleteInterrupt();
	}

	inline uint8_t readChannel(uint16_t channel) noexcept {
		if (channel <= Buffersize) {
			return this->data[(this->activeBuffer + 1) % 2][channel];
		}
		else {
			return 0;
		}
	}

	inline bool isStartbyteValid() noexcept {
		return (this->data[(this->activeBuffer + 1) % 2][0] == 0);
	}

private:
	inline void rxReadyCallback() noexcept {
		if (!this->usart.hasDataOverRunError()) {
			if (this->usart.hasFrameError()) {
				this->usart.read(); //clears error
				this->receiveIndex = 0;
			}
			else {
				this->data[this->activeBuffer][this->receiveIndex++] = this->usart.read();
				if (this->receiveIndex >= Buffersize) {
					this->activeBuffer = ((this->activeBuffer + 1) % 2);
					if (this->updateCallback != nullptr) {
						this->updateCallback->execute<AsynchronousTaskExecutionBehavior::REPEATEDLY>();
					}
					this->receiveIndex = 0;
				}
			}
		}
	}
};


#endif /* SRC_UTILITIES_COMMUNICATION_DMXCLIENT_HPP_ */
