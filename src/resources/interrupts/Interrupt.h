#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_


#include <avr/io.h>
#include "InterruptConfiguration.h"
#include "DefaultHandler.h"
#include "InterruptListener.h"


#if INTERRUPTTYPE == UNIVERSAL

class Interrupt final {

private:

	//Type declaration for callback
	typedef void(*Callback)(void);

	//Type declaration for universal target pointer
	typedef union {
		Callback callback;
		InterruptListener* listener;
	} TargetPointer;

	typedef struct {
		TargetPointer pointer;
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

	void registerCallback(Callback callback) noexcept;
	void registerListener(InterruptListener& listener) noexcept;

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

class Interrupt final {

private:

	//Type declaration for callback
	typedef void(*Callback)(void);

	template <uint8_t vectorNumber> inline static Callback& getTarget(){
		static Callback target = &DefaultHandler::nothing;
		return target;
	}

	Callback& target;

	inline Interrupt(Callback& target) noexcept : target(target) {}

public:

	template <uint8_t vectorNumber> static inline Interrupt Create() { return Interrupt(getTarget<vectorNumber>());}
	inline ~Interrupt() noexcept {}

	void registerCallback(Callback callback) noexcept;

	template <uint8_t vectorNumber> static inline void invoke() noexcept {
		getTarget<vectorNumber>()();
	}
};

#elif INTERRUPTTYPE == TRIGGER

class Interrupt final {

private:

	template <uint8_t vectorNumber> inline static InterruptListener*& getTarget(){
#if DEFAULT_TRIGGER_BEHAVIOR == INSERT_CHECK
		static InterruptListener* target = nullptr;
#elif DEFAULT_TRIGGER_BEHAVIOR == EMPTY_LISTENER
		static InterruptListener* target = &DefaultHandler::NoListener::getInstance();
#endif
		return target;
	}

	InterruptListener*& target;

	inline Interrupt(InterruptListener*& target) noexcept : target(target) {}

public:

	template <uint8_t vectorNumber> static inline Interrupt Create() { return Interrupt(getTarget<vectorNumber>());}
	inline ~Interrupt() noexcept {}

	void registerListener(InterruptListener& listener) noexcept;

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

class Interrupt final {
private:
	constexpr Interrupt() noexcept {}

public:

	template <uint8_t vectorNumber> static inline constexpr Interrupt Create() { return Interrupt();}
	inline ~Interrupt() noexcept {}

	template <uint8_t vectorNumber> static inline void invoke() noexcept { }
};

#endif


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_ */
