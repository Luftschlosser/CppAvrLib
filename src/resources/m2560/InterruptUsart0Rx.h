#ifndef SRC_RESOURCES_M2560_INTERRUPTUSART0RX_H_
#define SRC_RESOURCES_M2560_INTERRUPTUSART0RX_H_


#include "../interrupts/InterruptSource.h"
#include "../interrupts/InterruptConfiguration.h"
#include "../interrupts/IrqListener.h"
#include "../interrupts/DefaultHandler.h"

//inline void operator delete(void *p, unsigned int){}

#if ISRTYPE_USART0_RX == UNIVERSAL

namespace InterruptUsart0Rx {

	class Manager final : public InterruptSource {

	private:
		constexpr Manager() noexcept {}
		inline ~Manager() noexcept {}

	public:
		static InterruptSource::TargetPointer target;
		static bool callback;

		inline static InterruptSource* getInstance() noexcept {
			static Manager instance;
			return (InterruptSource*)&instance;
		}
		virtual void registerCallback(callback_t callback) noexcept;
		virtual void registerListener(IrqListener* listener) noexcept;
	};
}

#elif ISRTYPE_USART0_RX == CALLBACK

namespace InterruptUsart0Rx {

	class Manager final : public InterruptSource {

	private:
		constexpr Manager() noexcept {}
		inline ~Manager() noexcept {}

	public:
		static callback_t callback;

		inline static InterruptSource* getInstance() noexcept {
			static Manager instance;
			return (InterruptSource*)&instance;
		}
		virtual void registerCallback(callback_t callback) noexcept;
		virtual void registerListener(IrqListener* listener);
	};
}

#elif ISRTYPE_USART0_RX == TRIGGER

namespace InterruptUsart0Rx {

	class Manager final : public InterruptSource {

	private:
		constexpr Manager() noexcept {}
		inline ~Manager() noexcept {}

	public:
		static IrqListener* listener;

		inline static InterruptSource* getInstance() noexcept {
			static Manager instance;
			return (InterruptSource*)&instance;
		}
		virtual void registerCallback(callback_t callback);
		virtual void registerListener(IrqListener* listener) noexcept;
	};
}

#else

namespace InterruptUsart0Rx {

	class Manager final : public InterruptSource {

	private:
		constexpr Manager() noexcept {}
		inline ~Manager() noexcept {}

	public:
		inline static InterruptSource* getInstance() noexcept {
			static Manager instance;
			return (InterruptSource*)&instance;
		}
		virtual void registerCallback(callback_t callback);
		virtual void registerListener(IrqListener* listener);
	};
}

#endif

#endif /* SRC_RESOURCES_M2560_INTERRUPTUSART0RX_H_ */
