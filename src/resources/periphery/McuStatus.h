#ifndef SRC_RESOURCES_PERIPHERY_MCUSTATUS_H_
#define SRC_RESOURCES_PERIPHERY_MCUSTATUS_H_


#include <stdint.h>
#include "../Configuration.h"


///MMIO Abstraction of the MCU Status Register
class McuStatus final {
private:

	///No Constructor to prohibit instantiation
	McuStatus() = delete;

public:

	///The MCU Status Register
	union McuStatusReg {
		struct FIELDS {
			volatile uint8_t flagPORF : 1;	//Power-on Reset Flag
			volatile uint8_t flagEXTRF : 1;	//External Reset Flag
			volatile uint8_t flagBORF : 1;	//Brown-out Reset Flag
			volatile uint8_t flagWDRF : 1;	//Watchdog System Reset Flag
			volatile uint8_t flagJTRF : 1;	//JTAG Reset Flag (Only present on some AVRs)
		} fields;
		volatile uint8_t reg;
	} regMCUSR;

	enum ResetCondition : uint8_t {
		PowerOnReset = 0x01,
		ExternalReset = 0x02,
		BrownOutReset = 0x04,
		WatchdogReset = 0x08,
		JtagReset = 0x10
	};

	inline bool hasResetCondition(ResetCondition condition) const noexcept {
		return this->regMCUSR.reg & condition;
	}

	inline void clearResetCondition() noexcept {
		this->regMCUSR.reg = 0;
	}
};


#endif /* SRC_RESOURCES_PERIPHERY_MCUSTATUS_H_ */
