#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_


#include <avr/io.h>
#include "EventSource.h"
#include "Listener.h"
#include "InterruptConfiguration.h"

#include "DefaultHandler.h"


#if INTERRUPTTYPE == UNIVERSAL

class Interrupt final : public EventSource {

private:

	typedef struct {
		EventSource::TargetPointer pointer;
		bool callbackType;
	} TargetData;

	template <uint8_t vectorNumber> inline static TargetData& getTarget(){
		static TargetData target = {{&DefaultHandler::nothing}, true};
		return target;
	}

	TargetData& target;

	inline Interrupt(TargetData& target) noexcept : target(target) {}

public:

	template <uint8_t vectorNumber> static inline Interrupt Create() { return Interrupt(getTarget<vectorNumber>());}
	inline ~Interrupt() noexcept {}

	virtual void registerCallback(Callback callback) noexcept;
	virtual void registerListener(Listener& listener) noexcept;

	template <uint8_t vectorNumber> static inline void invoke() noexcept {
		if (getTarget<vectorNumber>().callbackType) {
			getTarget<vectorNumber>().pointer.callback();
		}
		else {
			getTarget<vectorNumber>().pointer.listener->trigger();
		}
	}
};

#elif INTERRUPTTYPE == CALLBACK

class Interrupt final : public EventSource {

private:
	static EventSource::Callback targets[_VECTORS_SIZE / 4];
	uint8_t vectorNumber;

public:
	constexpr Interrupt(uint8_t vectorNumber) noexcept : vectorNumber(vectorNumber - 1) {}
	inline ~Interrupt() noexcept {}
	virtual void registerCallback(Callback callback) noexcept;
	virtual void registerListener(Listener& listener);

	static inline void invoke(uint8_t vectorNumber) noexcept {
		vectorNumber--; //Array Access, Vector 1 -> Index 0
		Interrupt::targets[vectorNumber]();
	}
};

#elif INTERRUPTTYPE == TRIGGER

class Interrupt final : public EventSource {

private:
	static Listener* targets[_VECTORS_SIZE / 4];
	uint8_t vectorNumber;

public:
	constexpr Interrupt(uint8_t vectorNumber) noexcept : vectorNumber(vectorNumber - 1) {}
	inline ~Interrupt() noexcept {}
	virtual void registerCallback(Callback callback);
	virtual void registerListener(Listener& listener) noexcept;

	static inline void invoke(uint8_t vectorNumber) noexcept {
		vectorNumber--; //Array Access, Vector 1 -> Index 0
		Interrupt::targets[vectorNumber]->trigger();
	}
};

#else

class Interrupt final : public EventSource {

public:
	constexpr Interrupt(uint8_t vectorNumber) noexcept {}
	inline ~Interrupt() noexcept {}
	virtual void registerCallback(Callback callback);
	virtual void registerListener(Listener& listener);

	static inline void invoke(uint8_t vectorNumber) noexcept { }
};

#endif


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_ */
