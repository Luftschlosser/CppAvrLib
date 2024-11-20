#ifndef SRC_UTILITIES_TIME_STOPWATCH_HPP_
#define SRC_UTILITIES_TIME_STOPWATCH_HPP_


#include "../../resources/Periphery.h"
#include "../../resources/Interrupts.h"
#include <stdint.h>

class Stopwatch {

private:
	Timer16bit& timer;
	uint16_t offset;
	volatile uint16_t overflows;

	inline void timerOverflowCallback() noexcept {
		this->overflows++;
	}

public:
	inline Stopwatch(Timer16bit& timer, Interrupt timerOvfIrq) noexcept : timer(timer), offset(0), overflows(0) {
		timer.init();
		timer.setWaveformGenerationMode(Timer16bit::WaveformGenerationMode::NORMAL);
		timerOvfIrq.registerMethod<Stopwatch, &Stopwatch::timerOverflowCallback>(*this);
		timer.enableTimerOverflowInterrupt();
	}

	void start() noexcept;
	void stop() noexcept;

	inline void calibrate() noexcept {
		this->start();
		this->stop();
		this->offset = this->timer.getCounterValue();
	}

	inline uint16_t getTimerValue() noexcept {
		return this->timer.getCounterValue() - this->offset;
	}

	inline uint16_t getOverflowCount() noexcept {
		return this->overflows;
	}

	inline uint32_t getElapsedTicks() noexcept {
		return (this->overflows * 0xFFFF) + this->timer.getCounterValue() - this->offset;
	}

	inline uint32_t getElapsedMicroseconds() noexcept {
		return this->getElapsedTicks() / (F_CPU / 1000000);
	}

	inline uint16_t getElapsedMilliseconds() noexcept {
		return this->getElapsedTicks() / (F_CPU / 1000);
	}
};


#endif /* SRC_UTILITIES_TIME_STOPWATCH_HPP_ */
