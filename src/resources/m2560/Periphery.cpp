#include "Periphery.h"
#include "../../cpp/PlacementNew.h"
#include "../periphery/Port.h"

//Periphery definition for the ATmega2560

Port* Periphery::portA = new((void*)&PINA) Port();
Port* Periphery::portB = new((void*)&PINB) Port();
Port* Periphery::portC = new((void*)&PINC) Port();
Port* Periphery::portD = new((void*)&PIND) Port();
Port* Periphery::portE = new((void*)&PINE) Port();
Port* Periphery::portF = new((void*)&PINF) Port();
Port* Periphery::portG = new((void*)&PING) Port();
Port* Periphery::portH = new((void*)&PINH) Port();
Port* Periphery::portJ = new((void*)&PINJ) Port();
Port* Periphery::portK = new((void*)&PINK) Port();
Port* Periphery::portL = new((void*)&PINL) Port();


//Identity-Methods

template<> uint8_t Periphery::getIdentity<Port>(Port *periphery) noexcept {
	size_t adr = reinterpret_cast<size_t>(periphery);
	if (adr < 0x100) {
		return (adr - 0x20) / 0x3;
	}
	else {
		return ((adr - 0x100) / 0x3) + 0x7;
	}
}

/*
//GetInstance-Methods

template<> Port* Periphery::getInstance<Port>(uint8_t index) {
	if (index >= 11) {
		return nullptr; //throw later!
	}

	size_t adr = 0;
	if (index >= 7) {
		index -= 7;
		adr = (index*3) + 0x100;
	}
	else {
		adr = (index*3) + 0x20;
	}
	return (Port*)adr;//new((void*)adr) Port();
}

template<> Port* Periphery::getInstance<Port>(char letter) {
	uint8_t index = (uint8_t)(letter >= 'a' ? letter - 'a' : letter - 'A');
	if (index > 8) { //Port J/K/L
		index--;
	}
	return Periphery::getInstance<Port>(index);
}
*/
