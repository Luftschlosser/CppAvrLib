#ifndef SRC_UTILITIES_SCHEDULING_ASYNCHRONOUSTASK_HPP_
#define SRC_UTILITIES_SCHEDULING_ASYNCHRONOUSTASK_HPP_


#include <stdint.h>
#include <util/atomic.h>


///Enum declaration for possible template Parameter values.
enum AsynchronousTaskExecutionBehavior {
	ONCE,
	REPEATEDLY
};


///An instance of this class can store one function- or method call to be executed later.
///It is useful to schedule a task (for example in an ISR) to be executed later (for example in the main loop).
///\param Behavior This template parameter specifies whether the task will be cleared after execution or if the task will remain scheduled to be executed multiple times. [ONCE / REPEATEDLY].
template <AsynchronousTaskExecutionBehavior Behavior> class AsynchronousTask {

private:

	///Structure to hold the data needed to execute the task
	struct TaskData final {

		///The object upon to call scheduled class-methods respectively the argument with which to call scheduled functions.
		void* obj;

		///The pointer to the functions which wraps the actual function- or method call.
		void (*runner)(void* obj);
	};

	///The \see TaskData Instance used by this AsynchronousTask Instance.
	TaskData target;


	///Wrapper to call class-methods.
	template<class T, void(T::*method)()> static void callMethod(void* obj) noexcept {
		T* t = static_cast<T*>(obj);
		(t->*method)();
	}

	///Wrapper to call function with one argument.
	template<class T, void(*function)(T& data)> static void callFunction(void* obj) noexcept {
		T* t = static_cast<T*>(obj);
		function(*t);
	}

	///Wrapper to call function with no argument.
	template<void(*function)()> static void callFunction(void* obj) noexcept {
		function();
	}

public:

	///Constructor
	inline AsynchronousTask() noexcept : target({nullptr,nullptr}) {}

	///Removes any scheduled task from this AsynchronousTask instance.
	inline void clear() noexcept { this->target = {nullptr,nullptr}; }

	///Checks if this AsynchronousTask instance holds a task.
	///\returns true when a task is scheduled.
	inline bool hasTaskScheduled() const noexcept { return (this->target.runner != nullptr); }

	///Schedules a method call (Class Member) which takes no additional arguments.
	///\param T This template parameter specifies the class of which the method is part of.
	///\param method This template parameter specifies the method (at compiletime).
	///\param object A reference to the object upon which the method shall be called.
	template<class T, void (T::*method)()> inline void scheduleMethod(T& object) noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			this->target.obj = &object;
			this->target.runner = &callMethod<T, method>;
		}
	}


	///Schedules a function which takes one argument by reference.
	///\param T This template parameter specifies the type of argument the function takes.
	///\param function This template parameter specifies the function (at compiletime).
	///\param data A reference to the argument with which the function shall be called.
	template<typename T, void (*function)(T& data)> inline void scheduleFunction(T& data) noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			this->target.obj = &data;
			this->target.runner = &callFunction<T, function>;
		}
	}

	///Schedules a function which takes no argument.
	///\param function This template parameter specifies the function (at compiletime).
	template<void (*function)()> inline void scheduleFunction() noexcept {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			this->target.runner = &callFunction<function>;
		}
	}

	///Executes the scheduled function or method.
	inline void execute() noexcept {
		TaskData tmp;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			tmp = this->target;
			if (Behavior == ONCE) {
				this->clear();
			}
		}
		if (tmp.runner != nullptr) {
			tmp.runner(tmp.obj);
		}
	}
};


#endif /* SRC_UTILITIES_SCHEDULING_ASYNCHRONOUSTASK_HPP_ */
