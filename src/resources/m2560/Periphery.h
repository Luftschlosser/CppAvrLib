#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>
#include <stdlib.h>


//forward-declarations
class Port;


//Periphery declaration for the ATmega2560
class Periphery final {

public:

	//set false to disable runtime allocation.
	static constexpr bool runtimeAllocationsEnabled = true;


	//TODO: Storing everything even if not needed is wasteful... Access via getInstance() function?
	static Port* portA;
	static Port* portB;
	static Port* portC;
	static Port* portD;
	static Port* portE;
	static Port* portF;
	static Port* portG;
	static Port* portH;
	static Port* portJ;
	static Port* portK;
	static Port* portL;


	//Returns the Index of the specific periphery instance. [0-n]
	template <typename T> static constexpr uint8_t getIdentity(T* periphery) noexcept;

	//Returns the periphery instance with the specified index.
	template <typename T> inline static constexpr T& getInstance(uint8_t index);
	template <typename T> inline static constexpr T& getInstance(char letter);

	//Returns the total number of instances of the specified periphery type. [0-n]
	template <typename T> inline static constexpr uint8_t getCapacity() noexcept;

private:
	inline Periphery() noexcept {} //Don't allow instantiation
};

//template specializations
template <> inline constexpr uint8_t Periphery::getIdentity<Port>(Port* periphery) noexcept
{
	size_t adr = reinterpret_cast<size_t>(periphery);
	if (adr < 0x100) {
		return (adr - 0x20) / 0x3;
	}
	else {
		return ((adr - 0x100) / 0x3) + 0x7;
	}
}

template <> inline constexpr uint8_t Periphery::getCapacity<Port>() noexcept { return 11; }

template <> inline constexpr Port& Periphery::getInstance<Port>(uint8_t index) {
	if (index >= 11) {
		//TODO: throw later!
		index = 10;
	}

	uint16_t adr = index >= 7 ? ((index - 7) * 3) + 0x100 : (index*3) + 0x20;
	return *(reinterpret_cast<Port*>(adr)); //Direct cast for constexpr...
}
template <> inline constexpr Port& Periphery::getInstance<Port>(char letter) {
	/*switch(letter) {
	case 'A':
		return *(reinterpret_cast<Port*>(PINA));
	case 'B':
		return *(reinterpret_cast<Port*>(PINB));
	case 'C':
		return *(reinterpret_cast<Port*>(PINC));
	case 'D':
		return *(reinterpret_cast<Port*>(PIND));
	case 'E':
		return *(reinterpret_cast<Port*>(PINE));
	case 'F':
		return *(reinterpret_cast<Port*>(PINF));
	case 'G':
		return *(reinterpret_cast<Port*>(PING));
	case 'H':
		return *(reinterpret_cast<Port*>(PINH));
	case 'J':
		return *(reinterpret_cast<Port*>(PINJ));
	case 'K':
		return *(reinterpret_cast<Port*>(PINK));
	case 'L':
		return *(reinterpret_cast<Port*>(PINL));
	default:
		//TODO: throw
		return *((Port*)PINA);
	}*/
	uint8_t index = 10;
	if (letter >= 'A' && letter <= 'H')
		index = static_cast<uint8_t>(letter - 'A');
	else if (letter >= 'J' && letter <= 'L')
		index = static_cast<uint8_t>(letter - 'J') + 8;
	else {
		//TODO: throw;
	}
	return Periphery::getInstance<Port>(index);
}


#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
