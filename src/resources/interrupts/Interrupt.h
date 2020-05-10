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

	template <uint8_t vectorNumber> inline static Callback& getTarget(){
		static Callback target = &DefaultHandler::nothing;
		return target;
	}

	Callback& target;

	inline Interrupt(Callback& target) noexcept : target(target) {}

public:

	template <uint8_t vectorNumber> static inline Interrupt Create() { return Interrupt(getTarget<vectorNumber>());}
	inline ~Interrupt() noexcept {}

	virtual void registerCallback(Callback callback) noexcept;
	virtual void registerListener(Listener& listener);

	template <uint8_t vectorNumber> static inline void invoke() noexcept {
		getTarget<vectorNumber>()();
	}
};

#elif INTERRUPTTYPE == TRIGGER

class Interrupt final : public EventSource {

private:

	template <uint8_t vectorNumber> inline static Listener*& getTarget(){
#if DEFAULT_TRIGGER_BEHAVIOR == INSERT_CHECK
		static Listener* target = nullptr;
#elif DEFAULT_TRIGGER_BEHAVIOR == EMPTY_LISTENER
		static Listener* target = &DefaultHandler::NoListener::getInstance();
#endif
		return target;
	}

	Listener*& target;

	inline Interrupt(Listener*& target) noexcept : target(target) {}

public:

	template <uint8_t vectorNumber> static inline Interrupt Create() { return Interrupt(getTarget<vectorNumber>());}
	inline ~Interrupt() noexcept {}

	virtual void registerCallback(Callback callback) noexcept;
	virtual void registerListener(Listener& listener) noexcept;

	template <uint8_t vectorNumber> static inline void invoke() noexcept {
#if DEFAULT_TRIGGER_BEHAVIOR == INSERT_CHECK
		if (getTarget<vectorNumber>() != nullptr) {
			getTarget<vectorNumber>()->trigger();
		}
#elif DEFAULT_TRIGGER_BEHAVIOR == EMPTY_LISTENER
		getTarget<vectorNumber>()->trigger();
#endif
	}
};

#else

class Interrupt final : public EventSource {
private:
	constexpr Interrupt() noexcept {}

public:

	template <uint8_t vectorNumber> static inline constexpr Interrupt Create() { return Interrupt();}
	inline ~Interrupt() noexcept {}

	virtual void registerCallback(Callback callback);
	virtual void registerListener(Listener& listener);

	template <uint8_t vectorNumber> static inline void invoke() noexcept { }
};

#endif


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_ */
