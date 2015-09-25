#include <boundedbuffer.h>

int32 A[15];                 //Definition for bounded buffer A
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/
int32 prod, con;
sid32 consumed, produced;

shellcmd xsh_boundedbuffer(int nargs, char *args[])
{
	int32 count = 5;
	int32 TempCount = atoi(args[1]);
	consumed = semcreate(1);
	produced = semcreate(0);
	/* Output info for '--help' argument */


	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tThe producer and the consumer with bounded buffer.\n\n");
		printf("\tThe producer's job is to generate a piece of data, put it into \
the buffer and start again. At the same time, the consumer is consuming the data \
(i.e., removing it from the buffer) one piece at a time.\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	if (nargs > 2)
		printf("Too many arguments\n");
	else {
		if (nargs == 2)
		{
			count = TempCount;
		}
		//create the process producer and consumer and put them in ready queue.     
		resume( create(bb_producer, 1024, 20, "producer", 3, count, consumed, produced) );
		resume( create(bb_consumer, 1024, 20, "consumer", 3, count, consumed, produced) );
	}
	return 0;
}