#ifndef SRC_UTILITIES_STREAMING_STREAM_HPP_
#define SRC_UTILITIES_STREAMING_STREAM_HPP_


#include <stdint.h>


template<typename T> class Stream {
public:
	virtual ~Stream() noexcept {}
	virtual bool hasNextStreamToken() noexcept;
	virtual T getNextStreamToken() noexcept;
};


#endif /* SRC_UTILITIES_STREAMING_STREAM_HPP_ */
