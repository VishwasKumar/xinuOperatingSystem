#include <boundedbuffer.h>
//Code to consume values of global variable 'n' until the value of n is less than or equal to count
void bb_consumer(int32 count, sid32 consumed, sid32 produced)
{
	int32 i, j;
	con = 0;
    for (j = 0; j < count; j++)
    {
	wait(produced);
    for (i = 0; i < 15; i++)
    {
    	kprintf("consumed :%d\n", A[con]);//print consumed value e.g. consumed : 8
    	con = (con + 1) % 15;
    }
    signal(consumed);
}
    exit(0);
}