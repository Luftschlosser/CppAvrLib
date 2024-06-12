#ifndef SRC_UTILITIES_DATASTRUCTURES_BITMASK_HPP_
#define SRC_UTILITIES_DATASTRUCTURES_BITMASK_HPP_


#include <stdint.h>


template<typename AddressType, AddressType Size> class Bitmask {

private:

	static constexpr AddressType arraySize = (Size+7)/8;

	uint8_t mask[arraySize];

public:

	inline Bitmask() noexcept {
		for (uint8_t i = 0; i < ((Size+7)/8); i++) {
			this->mask[i] = 0;
		}
	}

	inline uint8_t getByte(AddressType byteIndex) noexcept {
		return this->mask[byteIndex];
	}

	inline void setByte(AddressType byteIndex, uint8_t byte) noexcept {
		if (byteIndex < arraySize) {
			this->mask[byteIndex] = byte;
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

	inline bool hasAnyBitSet() noexcept {
		for (AddressType i = 0; i < arraySize; i++) {
			if (this->mask[i] > 0) {
				return true;
			}
		}
		return false;
	}

	inline void clearAllBits() noexcept {
		for (AddressType i = 0; i < arraySize; i++) {
			this->mask[i] = 0;
		}
	}
};


#endif /* SRC_UTILITIES_DATASTRUCTURES_BITMASK_HPP_ */
