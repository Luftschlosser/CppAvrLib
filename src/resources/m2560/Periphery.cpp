#include "Periphery.h"
#include "../../cpp/PlacementNew.h"
#include "../periphery/Port.h"

//Periphery definition for the ATmega2560
namespace Periphery {

	Port* portA = new((void*)&PINA) Port();
	Port* portB = new((void*)&PINB) Port();
	Port* portC = new((void*)&PINC) Port();
	Port* portD = new((void*)&PIND) Port();
	Port* portE = new((void*)&PINE) Port();
	Port* portF = new((void*)&PINF) Port();
	Port* portG = new((void*)&PING) Port();
	Port* portH = new((void*)&PINH) Port();
	Port* portJ = new((void*)&PINJ) Port();
	Port* portK = new((void*)&PINK) Port();
	Port* portL = new((void*)&PINL) Port();


	//Identity-Methods
	template<> uint8_t getIdentity<Port>(Port *periphery) noexcept {
		size_t adr = reinterpret_cast<size_t>(periphery);
		if (adr < 0x100) {
			return (adr - 0x20) / 0x3;
		}
		else {
			return ((adr - 0x100) / 0x3) + 0x7;
		}
	}

	//GetInstance-Methods
	template<> Port* getInstance<Port>(uint8_t index) {
		switch (index) {
		case 0: //A
			return portA;
		case 1: //B
			return portB;
		case 2: //C
			return portC;
		case 3: //D
			return portD;
		case 4: //E
			return portE;
		case 5: //F
			return portF;
		case 6: //G
			return portG;
		case 7: //H
			return portH;
		case 8: //J
			return portJ;
		case 9: //K
			return portK;
		case 10: //L
			return portL;
		default:
			return nullptr; //throw later!
		}
	}
}
