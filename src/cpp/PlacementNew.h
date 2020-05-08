#ifndef SRC_CPP_PLACEMENTNEW_H_
#define SRC_CPP_PLACEMENTNEW_H_


#include <stdlib.h>

inline void* operator new (size_t, void* ptr) {return ptr;};
inline void* operator new[](size_t, void* ptr) { return ptr; }
inline void  operator delete  (void*, void*) { }
inline void  operator delete[](void*, void*) { }

#endif /* SRC_CPP_PLACEMENTNEW_H_ */
