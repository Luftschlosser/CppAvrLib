#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>

//forward-declarations
class Port;


//Periphery declaration for the ATmega2560
namespace Periphery {

	//set false to disable runtime allocation.
	constexpr bool runtimeAllocationsEnabled = true;


	//TODO: Storing everything even if not needed is wasteful... Access via function?
	extern Port* portA;
	extern Port* portB;
	extern Port* portC;
	extern Port* portD;
	extern Port* portE;
	extern Port* portF;
	extern Port* portG;
	extern Port* portH;
	extern Port* portJ;
	extern Port* portK;
	extern Port* portL;


	//Returns the Index of the specific periphery instance. [0-n]
	template <typename T> uint8_t getIdentity(T *periphery);
	template<> uint8_t getIdentity<Port>(Port *periphery) noexcept;

	//Returns the periphery instance with the specified index.
	template <typename T> T* getInstance(uint8_t index);
	template<> Port* getInstance<Port>(uint8_t index);

	//Returns the total number of instances of the specified periphery type. [0-n]
	template <typename T> constexpr uint8_t getCapacity() noexcept { return 0; }
	template <> uint8_t constexpr getCapacity<Port>() noexcept { return 11; }
}


#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
