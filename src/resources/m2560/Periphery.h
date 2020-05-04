#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>
#include <stdlib.h>


//forward-declarations
class Port;

//Periphery declaration for the ATmega2560
namespace Periphery {

	//set false to disable runtime allocation.
	static constexpr bool runtimeAllocationsEnabled = true;


	//TODO: Inhibit Warnings with some trick
	static Port& portA = *(reinterpret_cast<Port*>(PINA));
	static Port& portB = *(reinterpret_cast<Port*>(PINB));
	static Port& portC = *(reinterpret_cast<Port*>(PINC));
	static Port& portD = *(reinterpret_cast<Port*>(PIND));
	static Port& portE = *(reinterpret_cast<Port*>(PINE));
	static Port& portF = *(reinterpret_cast<Port*>(PINF));
	static Port& portG = *(reinterpret_cast<Port*>(PING));
	static Port& portH = *(reinterpret_cast<Port*>(PINH));
	static Port& portJ = *(reinterpret_cast<Port*>(PINJ));
	static Port& portK = *(reinterpret_cast<Port*>(PINK));
	static Port& portL = *(reinterpret_cast<Port*>(PINL));


	//Returns the Index of the specific periphery instance. [0-n]
	template <typename T> static constexpr uint8_t getIdentity(T* periphery) noexcept;

	template <> inline constexpr uint8_t getIdentity<Port>(Port* periphery) noexcept
	{
		size_t adr = reinterpret_cast<size_t>(periphery);
		if (adr < 0x100) {
			return (adr - 0x20) / 0x3;
		}
		else {
			return ((adr - 0x100) / 0x3) + 0x7;
		}
	}


	//Returns the periphery instance with the specified index.
	template <typename T> inline static constexpr T& getInstance(uint8_t index);
	template <typename T> inline static constexpr T& getInstance(char letter);

	template <> inline constexpr Port& getInstance<Port>(uint8_t index) {
		if (index >= 11) {
			//TODO: throw later!
			index = 10;
		}

		uint16_t adr = index >= 7 ? ((index - 7) * 3) + 0x100 : (index*3) + 0x20;
		return *(reinterpret_cast<Port*>(adr)); //Direct cast for constexpr...
	}

	template <> inline constexpr Port& getInstance<Port>(char letter) {
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


	//Returns the total number of instances of the specified periphery type. [0-n]
	template <typename T> inline static constexpr uint8_t getCapacity() noexcept;

	template <> inline constexpr uint8_t getCapacity<Port>() noexcept { return 11; }
}

#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
