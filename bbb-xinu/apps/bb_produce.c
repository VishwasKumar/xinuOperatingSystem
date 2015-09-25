 #include <boundedbuffer.h>

 void bb_producer(int32 count, sid32 consumed, sid32 produced)
 {
 	int32 i, j;
 	prod = 0;
 	for (j = 0; j < count; j++)
 	{
 	wait(consumed);
 	for (i = 0; i < 15; i++) //Code to produce values less than equal to count
 	{
 		A[prod] = i; //produced value should get assigned to bounded buffer A
 		kprintf("produced : %d\n", A[prod]); //print produced value e.g. produced : 8
 		prod = (prod + 1) % 15;
 	}
 	signal(produced);
 }
 	exit(0);
 }