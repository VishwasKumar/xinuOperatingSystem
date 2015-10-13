#include <prodcons.h>

/*
*Description
*Get the value of a future set by an operation and change the state of future from FUTURE_VALID to FUTURE_EMPTY.
*Parameters
*future *f: future on which to wait for and obtain value
*int *value: variable in which to obtain the value from a future
*Return
*syscall: SYSERR or OK
*/

syscall future_get(future *f, int *value){

	intmask mask;
	mask = disable();

	if (f->state==FUTURE_EMPTY && f->tid==NULL)
	{
		
		f->tid=getpid(); //set id
		f->state=FUTURE_WAITING; // set state
		wait(f->wait);
		if(f->state==FUTURE_VALID){
			f->state=FUTURE_EMPTY;
			// *value=*(f->value);
			f->tid=NULL; // reset tid
			restore(mask);
			return OK;
		}
	}
	restore(mask);
	return SYSERR;
}