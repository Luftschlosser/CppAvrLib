#ifndef SRC_UTILITIES_MEMORY_MEMORYPOOL_HPP_
#define SRC_UTILITIES_MEMORY_MEMORYPOOL_HPP_


#include "../datastructures/Bitmask.hpp"


template <uint8_t ChunkSize, typename AddressType, AddressType NumberOfChunks> class MemoryPool {

private:
	Bitmask<AddressType, NumberOfChunks> usageMask;
	char pool[ChunkSize][NumberOfChunks];

	inline bool isMemoryLocationWithinPool(void* location) noexcept {
		if ((location >= pool) && (location < (pool + sizeof(pool)))) {
			return true;
		}
		else {
			return false;
		}
	}

	inline AddressType fromMemoryLocationToIndex(void* location) noexcept {
		return (reinterpret_cast<intptr_t>(location) - this->pool) / ChunkSize;
	}

	inline void* fromIndexToMemoryLocation(AddressType index) noexcept {
		return reinterpret_cast<void*>(this->pool[index]);
	}

public:
	inline bool isFull() noexcept {
		return this->usageMask.hasAllBitsSet();
	}

	inline void* allocateChunk() noexcept {
		AddressType chunkNumber = 0;
		do {
			if (!this->usageMask.isSet(chunkNumber)) {
				this->usageMask.setBit(chunkNumber);
				return this->fromIndexToMemoryLocation(chunkNumber);
			}
		} while (++chunkNumber < NumberOfChunks);
		return nullptr;
	}

	inline void freeChunk(void* chunk) noexcept {
		this->usageMask.clearBit(this->fromMemoryLocationToIndex(chunk));
	}
};


#endif /* SRC_UTILITIES_MEMORY_MEMORYPOOL_HPP_ */
