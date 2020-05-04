#ifndef SRC_RESOURCES_M2560_PERIPHERY_H_
#define SRC_RESOURCES_M2560_PERIPHERY_H_


#include <avr/io.h>

#include <stdint.h>

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
	template <typename T> static uint8_t getIdentity(T* periphery) noexcept;

	//Returns the periphery instance with the specified index.
	template <typename T> inline static constexpr T& getInstance(uint8_t index);
	template <typename T> inline static constexpr T& getInstance(char letter);

	//Returns the total number of instances of the specified periphery type. [0-n]
	template <typename T> inline static constexpr uint8_t getCapacity() noexcept;

private:
	inline Periphery() noexcept {} //Don't allow instantiation
};

//template specializations
template <> inline constexpr uint8_t Periphery::getCapacity<Port>() noexcept { return 11; }
template <> inline constexpr Port& Periphery::getInstance<Port>(uint8_t index) { //Todo: make it return Reference instead of Pointer? -> Page 71: https://aristeia.com/TalkNotes/C++_Embedded_Deutsch.pdf
	if (index >= 11) {
		//TODO: throw later!
		index = 10;
	}

	uint16_t adr = index >= 7 ? ((index - 7) * 3) + 0x100 : (index*3) + 0x20;
	return *((Port*)adr); //Direct cast for constexpr... TODO: ReinterpretCast
}
template <> inline constexpr Port& Periphery::getInstance<Port>(char letter) {
	/*switch(letter) {
	case 'A':
		return *((Port*)PINA); //TODO: ReinterpretCast
	case 'B':
		return *((Port*)PINB); //TODO: ReinterpretCast
	case 'C':
		return *((Port*)PINC); //TODO: ReinterpretCast
	case 'D':
		return *((Port*)PIND); //TODO: ReinterpretCast
	case 'E':
		return *((Port*)PINE); //TODO: ReinterpretCast
	case 'F':
		return *((Port*)PINF); //TODO: ReinterpretCast
	case 'G':
		return *((Port*)PING); //TODO: ReinterpretCast
	case 'H':
		return *((Port*)PINH); //TODO: ReinterpretCast
	case 'J':
		return *((Port*)PINJ); //TODO: ReinterpretCast
	case 'K':
		return *((Port*)PINK); //TODO: ReinterpretCast
	case 'L':
		return *((Port*)PINL); //TODO: ReinterpretCast
	default:
		//TODO: throw
		return *((Port*)PINA);
	}*/
	uint8_t index = (uint8_t)(letter >= 'a' ? letter - 'a' : letter - 'A');
	if (index > 8) { //Port J/K/L
		index--;
	}
	return Periphery::getInstance<Port>(index);
}


#endif /* SRC_RESOURCES_M2560_PERIPHERY_H_ */
