#include "Stopwatch.hpp"

void Stopwatch::start() noexcept {
	this->overflows = 0;
	this->timer.setCounterValue(0);
	this->timer.setClockSelect(Timer16bit::ClockSelect::PRESCALE_1);
}

void Stopwatch::stop() noexcept {
	this->timer.setClockSelect(Timer16bit::ClockSelect::NONE);
}
