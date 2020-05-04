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
