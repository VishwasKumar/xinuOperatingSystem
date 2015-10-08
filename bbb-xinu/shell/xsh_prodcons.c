#include <prodcons.h>



future *f1, *f2, *f3;
int32 n;                 //Definition for global variable 'n'
/*Now global variable n will be on Heap so it is accessible all the processes i.e. consume and produce*/
sid32 consumed, produced; // Definition of Semaphores

shellcmd xsh_prodcons(int nargs, char *args[])
{
	int32 count = 2000;
	int32 flag_future = 0; // initialise flag to 0

	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tThe producer and the consumer with Semaphores.\n\n");
		printf("\tThe producer's job is to generate a piece of data, put it into \
the buffer and start again. At the same time, the consumer is consuming the data \
(i.e., removing it from the buffer) one piece at a time.\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	if (nargs > 2){
		printf("Too many arguments\n");
		return 0;
	}
	else if (nargs == 1)
		flag_future =0;

	else if (nargs == 2){
		if ( strncmp(args[1],"-f", 10) == 0){
			flag_future = 1;
		}
		else if (atoi(args[1]) <= 0)
		{
			printf("Please enter positive value greater that 0\n");
			return 0;
		}
		else{
			flag_future = 0;
			count = atoi(args[1]);
		}
	}
	else{
		printf("Invalid arguments\n Use --help \n");
		return 0;
	}		
	if (flag_future == 0)
	{
		consumed = semcreate(1);
		produced = semcreate(0);
		//create the process producer and consumer and put them in ready queue.     
	 	resume( create(producer, 1024, 20, "producer", 3, count, consumed, produced) );
	 	resume( create(consumer, 1024, 20, "consumer", 3, count, consumed, produced) );
	}

	else{
  		f1 = future_alloc(FUTURE_EXCLUSIVE);
  		f2 = future_alloc(FUTURE_EXCLUSIVE);
  		f3 = future_alloc(FUTURE_EXCLUSIVE);
 
  		resume( create(future_cons, 1024, 20, "fcons1", 1, f1) );
  		resume( create(future_prod, 1024, 20, "fprod1", 1, f1) );
  		resume( create(future_cons, 1024, 20, "fcons2", 1, f2) );
  		resume( create(future_prod, 1024, 20, "fprod2", 1, f2) );
  		resume( create(future_cons, 1024, 20, "fcons3", 1, f3) );
  		resume( create(future_prod, 1024, 20, "fprod3", 1, f3) );
	}
	return 0;
}