#ifndef SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_
#define SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_


#include <util/atomic.h>


///Instances of this class are an abstract representation of an interrupt source.
///Handlers can be registered at runtime, but only the last registered handler will be invoked when an interrupt occurs!
class Interrupt final {

private:

	///Structure to hold the data needed to invoke a handler
	struct Delegate final {

		///The object upon to invoke registered class-methods respectively the argument with which to call registered functions.
		void* obj;

		///The pointer to the functions which wraps the actual handler invocation.
		void (*invoker)(void* obj) noexcept;
	};

	///Empty function to serve as default handler.
	static void invokeNothing(void* obj) noexcept {}

	///Wrapper to invoke class-methods
	template<class T, void(T::*method)()> static void invokeMethod(void* obj) noexcept {
		T* t = static_cast<T*>(obj);
		(t->*method)();
	}

	///Wrapper to invoke function with one argument.
	template<class T, void(*function)(T& data)> static void invokeFunction(void* obj) noexcept {
		T* t = static_cast<T*>(obj);
		function(*t);
	}

	///Wrapper to invoke function with no argument.
	template<void(*function)()> static void invokeFunction(void* obj) noexcept {
		function();
	}

	///Provides unique instances of \see Delegate for each ISR-Vector-Number.
	///\param vectorNumber This template parameter specifies the vectorNumber represented by the returned Delegate.
	///\return A reference to the specified \see Delegate Instance.
	template <uint8_t vectorNumber> inline static Delegate& getTarget() noexcept {
		static Delegate target = {nullptr, &invokeNothing};
		return target;
	}

	///The \see Delegate Instance used by this Interrupt Instance.
	Delegate& target;

	///Constructor
	///\param target The \see Delegate Instance which shall be used by this Interrupt.
	inline Interrupt(Delegate& target) noexcept : target(target) {}

public:

	///Factory for Interrupt-Instances which are paired to a specified ISR-vector
	///\param vectorNumber This template parameter specifiess the Vector-Number of the ISR the created Interrupt-Instance shall represent.
	template <uint8_t vectorNumber> static inline Interrupt GetInstance() noexcept { return Interrupt(getTarget<vectorNumber>());}

	///Default Destructor
	inline ~Interrupt() noexcept {}

	///Registers a method (Class Member) as handler which takes no additional arguments.
	///\param T This template parameter specifies the class of which the method is part of.
	///\param method This template parameter specifies the handler method (at compiletime).
	///\param object A reference to the object upon which the method shall be called.
	template<class T, void (T::*method)()> inline void registerMethod(T& object) noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			target.obj = &object;
			target.invoker = &invokeMethod<T, method>;
		}
	}


	///Registers a function as handler which takes one argument by reference.
	///\param T This template parameter specifies the type of argument the function takes.
	///\param function This template parameter specifies the handler function (at compiletime).
	///\param data A reference to the argument with which the function shall be called.
	template<typename T, void (*function)(T& data)> inline void registerFunction(T& data) noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			target.obj = &data;
			target.invoker = &invokeFunction<T, function>;
		}
	}

	///Registers a function as handler which takes no argument.
	///\param function This template parameter specifies the handler function (at compiletime).
	template<void (*function)()> inline void registerFunction() noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			target.invoker = &invokeFunction<function>;
		}
	}

	///Invokes this Interrupt and calls the registered handler.
	///Can be used to trigger a synchronous software-interrupt.
	inline void invoke() noexcept {
		target.invoker(target.obj);
	}

	///Used to invoke the Interrupt with the template-specified vectornumber.
	///It is used by the ISR-Routines to call the registered handler.
	///Don't call this function unless you are sure what you are doing!
	///\param vectorNumber This template-parameter specifies the ISR-Vector-Number of the Interrupt to invoke.
	template <uint8_t vectorNumber> static inline void invoke() noexcept {
		Delegate& target = getTarget<vectorNumber>();
		target.invoker(target.obj);
	}
};


#endif /* SRC_RESOURCES_INTERRUPTS_INTERRUPT_H_ */
