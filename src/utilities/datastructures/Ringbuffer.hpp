#ifndef SRC_UTILITIES_DATASTRUCTURES_RINGBUFFER_HPP_
#define SRC_UTILITIES_DATASTRUCTURES_RINGBUFFER_HPP_


#include <stdint.h>


template<typename T, typename SizeType, SizeType Size> class Ringbuffer {
private:
	volatile SizeType inputIndex;
	SizeType outputIndex;
	T buffer[Size];

public:
	Ringbuffer() noexcept : inputIndex(0), outputIndex(0) {}

	inline bool inputNewElement(T element) noexcept {
		this->inputIndex = (this->inputIndex + 1) % Size;
		this->buffer[this->inputIndex] = element;
		return (this->inputIndex != this->outputIndex);
	}

	inline bool hasNextElement() noexcept {
		return (this->inputIndex != this->outputIndex);
	}

	inline T getNextElement() noexcept {
		this->outputIndex = (this->outputIndex + 1) % Size;
		return this->buffer[this->outputIndex];
	}
};


#endif /* SRC_UTILITIES_DATASTRUCTURES_RINGBUFFER_HPP_ */
