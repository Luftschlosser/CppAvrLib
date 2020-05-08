#include "VirtualMembers.h"

extern "C" int __cxa_guard_acquire(__guard *g)
{
	return !*(char *)(g);
}
extern "C" void __cxa_guard_release (__guard *g)
{
	*(char *)g = 1;
}
extern "C" void __cxa_guard_abort (__guard *) { }
extern "C" void __cxa_pure_virtual(void) { }
extern "C" void atexit( void ) { } //µC will never "exit", so atexit can be dummy.
