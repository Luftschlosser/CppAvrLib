#ifndef SRC_RESOURCES_INTERRUPTS_DEFAULTHANDLER_H_
#define SRC_RESOURCES_INTERRUPTS_DEFAULTHANDLER_H_

#include "Listener.h"

namespace DefaultHandler {

	//Default-Function to call when no callback is registered
	inline void nothing() noexcept {}


	//Default-IrqListener to trigger when no Listener is registered
	class NoListener final : public Listener {

	private:

		inline constexpr NoListener() noexcept {}
		inline ~NoListener() noexcept {}

	public:
		inline static Listener& getInstance() noexcept {
			static NoListener instance;
			return instance;
		}
		virtual inline void trigger() noexcept {}
	};
}


#endif /* SRC_RESOURCES_INTERRUPTS_DEFAULTHANDLER_H_ */
