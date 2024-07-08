#ifndef SRC_UTILITIES_STREAMING_STREAM_HPP_
#define SRC_UTILITIES_STREAMING_STREAM_HPP_


#include <stdint.h>


template<typename T> class Stream {
public:
	virtual ~Stream() noexcept {}
	virtual bool hasNextStreamToken() noexcept = 0;
	virtual T getNextStreamToken() noexcept = 0;
};


#endif /* SRC_UTILITIES_STREAMING_STREAM_HPP_ */
