#ifndef SRC_UTILITIES_DATASTRUCTURES_BITMASK_HPP_
#define SRC_UTILITIES_DATASTRUCTURES_BITMASK_HPP_


#include <stdint.h>


template<typename AddressType, AddressType Size> class Bitmask {

private:

	uint8_t mask[(Size+7)/8];

public:

	inline Bitmask() noexcept {
		for (uint8_t i = 0; i < ((Size+7)/8); i++) {
			this->mask[i] = 0;
		}
	}

	inline void setBit(AddressType position) noexcept {
		this->mask[position/8] |= 1 << (position % 8);
	}

	inline void clearBit(AddressType position) noexcept {
		this->mask[position/8] &= ~(1 << (position % 8));
	}

	inline bool isSet(AddressType position) noexcept {
		return (this->mask[position/8] & (1 << (position % 8)));
	}
};


#endif /* SRC_UTILITIES_DATASTRUCTURES_BITMASK_HPP_ */
