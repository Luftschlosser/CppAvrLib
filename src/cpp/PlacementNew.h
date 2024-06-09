#ifndef SRC_CPP_PLACEMENTNEW_H_
#define SRC_CPP_PLACEMENTNEW_H_


#include <stdlib.h>

inline void* operator new (size_t, void* ptr) noexcept { return ptr; }
inline void* operator new[](size_t, void* ptr) noexcept { return ptr; }
inline void  operator delete  (void*, void*) noexcept { }
inline void  operator delete[](void*, void*) noexcept { }

//Todo: Trap! (Should never be called, only needed for Linking) -> https://stackoverflow.com/questions/78572944/why-is-placement-new-for-classes-with-virtual-members-only-working-when-buffer#78573012
inline void operator delete(void*, unsigned int) noexcept { }

#endif /* SRC_CPP_PLACEMENTNEW_H_ */
