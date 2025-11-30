# CppAvrLib

**CppAvrLib** is a minimalist object oriented C++ hardware abstraction layer for AVR ATmega microcontrollers. I needed a better way to program my Arduino-Nano and Arduino-Mega boards without relying on the horribly flawed Arduino library. The library aims to provide zero-overhead wrappers for common periphery, while not compromising code structure and cleanliness. I've implemented features for my own uses as I needed them, so it's is not complete in any way and might be extended in the future.

It consists of memory-mapped IO abstractions, a very efficient delegate handler for hardware Interrupts, as well as various utilities for common protocols, memory management, time and scheduled tasks.

## Periphery

The following periphery wrappers have been implemented as memory-mapped objects

- GPIO Ports & Pins (including external Interrupt Pins and Pin change Interrupts)
- USART
- TWI (I2C)
- Timers (16bit / 8bit / asynchronous)
- ADC
- Watchdog
- General Purpose Registers
- Eeprom

Peripheries can be accessed via `resources/Periphery.h`.
Interrupt delegate handlers can be accessed via `resources/Interrupts.h` and enabled in `resources/Configuration.h`.

All peripheries were intended to be allocated/deallocated at runtime, but that mechanism turned out to be unnecessary for most use-cases, so the implementation is incomplete (missing errorhandling) and I recommend disabling it in `resources/Configuration.h`.

## Supported Microcontrollers

Currently the library is implemented for 3 types of AVR microcontrollers:

- AVR ATmega 328p (Commonly used in Arduino Uno / Arduino Nano)
- AVR ATmega 328pb (New revision of 328p)
- AVR ATmega 2560 (Commonly used in Arduino Mega)

## Example usage

Check `main.cpp` to see some example usage.
