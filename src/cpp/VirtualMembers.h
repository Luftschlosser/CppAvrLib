#ifndef SRC_CPP_VIRTUALMEMBERS_H_
#define SRC_CPP_VIRTUALMEMBERS_H_


//src: https://www.avrfreaks.net/forum/avr-c-micro-how?page=all
__extension__ typedef int __guard __attribute__((mode (__DI__)));
extern "C" int __cxa_guard_acquire(__guard *g);
extern "C" void __cxa_guard_release (__guard *g);
extern "C" void __cxa_guard_abort (__guard *);
extern "C" void __cxa_pure_virtual(void);
extern "C" void	atexit( void );


#endif /* SRC_CPP_VIRTUALMEMBERS_H_ */
