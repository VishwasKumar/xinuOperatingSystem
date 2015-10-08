#include <prodcons.h>

/*
*Description
*Set a value in a future and changes state from FUTURE_EMPTY or FUTURE_WAITING to FUTURE_VALID.
*Parameters
*future *f: future in which to set the value int *value: result of an operation to be set as value in a future
*Return
*syscall: SYSERR or OK
*/

syscall future_set(future *f, int *value){
	intmask mask;
	mask = disable();
	if(f->state==FUTURE_WAITING || f->state==FUTURE_EMPTY){
		f->value=*value;
		f->state=FUTURE_VALID;
		signal(f->wait);
		restore(mask);
		return OK;
	}
	restore(mask);
	return SYSERR;
}