#include <prodcons.h>

/*
*Description
*Free the allocated future. This function will simply free the space assigned to Future. Use memfree(). call to free the space.
*Parameters
*future* f: future to free
*Return
*syscall: SYSERR or OK
*/

syscall future_free(future* f){
	intmask mask;
	mask = disable();
	semdelete(f->wait);
	restore(mask);
	return freemem(f, sizeof(future));
}
