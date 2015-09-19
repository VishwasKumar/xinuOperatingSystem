#include <prodcons.h>

int32 n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/

shellcmd xsh_prodcons(int nargs, char *args[])
{
	int32 count = 2000;
	int32 tempCount = atoi(args[1]);
	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tThe producer and the consumer.\n\n");
		printf("\tThe producer's job is to generate a piece of data, put it into \
the buffer and start again. At the same time, the consumer is consuming the data \
(i.e., removing it from the buffer) one piece at a time.\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	if (nargs > 2)
		printf("Too many arguments\n");
	else if (tempCount > 0){
		if (nargs == 2)
			count = tempCount;
		//create the process producer and consumer and put them in ready queue.     
		resume( create(producer, 1024, 20, "producer", 1, count) );
		resume( create(consumer, 1024, 20, "consumer", 1, count) );
	}
	return 0;
}