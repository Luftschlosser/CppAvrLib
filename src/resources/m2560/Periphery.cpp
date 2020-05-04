#include "Periphery.h"
#include "../periphery/Port.h"

//Periphery definition for the ATmega2560

Port* Periphery::portA = (reinterpret_cast<Port*>(PINA));
Port* Periphery::portB = (reinterpret_cast<Port*>(PINB));
Port* Periphery::portC = (reinterpret_cast<Port*>(PINC));
Port* Periphery::portD = (reinterpret_cast<Port*>(PIND));
Port* Periphery::portE = (reinterpret_cast<Port*>(PINE));
Port* Periphery::portF = (reinterpret_cast<Port*>(PINF));
Port* Periphery::portG = (reinterpret_cast<Port*>(PING));
Port* Periphery::portH = (reinterpret_cast<Port*>(PINH));
Port* Periphery::portJ = (reinterpret_cast<Port*>(PINJ));
Port* Periphery::portK = (reinterpret_cast<Port*>(PINK));
Port* Periphery::portL = (reinterpret_cast<Port*>(PINL));
