#include <prodcons.h>



future  *f_exclusive,  *f_shared,  *f_queue;
int32 n; 
int set_head = 0;
int set_tail = 0;

int get_head = 0;
int get_tail = 0;

future set_q[5];
future get_q[5];

                //Definition for global variable 'n'
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
		printf("\tThe producer and the consumer with Semaphores.\n");
		printf("\tThe producer's job is to generate a piece of data, put it into \
the buffer and start again. At the same time, the consumer is consuming the data \
(i.e., removing it from the buffer) one piece at a time.\n\n");
		printf("-f\t Use futures concept to produce a random value in the future, while the consumer waits for the value which \
will be set in the future\n\n");
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

        f_exclusive  =  future_alloc(FUTURE_EXCLUSIVE);
        f_shared  =  future_alloc(FUTURE_SHARED);
        f_queue  =  future_alloc(FUTURE_QUEUE);

        //Test FUTURE_EXCLUSIVE
  		resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
  		resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );
 
 		// Test FUTURE_SHARED
        resume(  create(future_cons,  1024,  20,  "fcons2",  1,  f_shared)  );
        resume(  create(future_cons,  1024,  20,  "fcons3",  1,  f_shared)  );
        resume(  create(future_cons,  1024,  20,  "fcons4",  1,  f_shared)  );  
        resume(  create(future_cons,  1024,  20,  "fcons5",  1,  f_shared)  );  
        resume(  create(future_prod,  1024,  20,  "fprod2",  1,  f_shared)  );
        
        //  Test  FUTURE_QUEUE
        resume(  create(future_cons,  1024,  20,  "fcons6",  1,  f_queue)  );
        resume(  create(future_cons,  1024,  20,  "fcons7",  1,  f_queue)  );
        resume(  create(future_cons,  1024,  20,  "fcons7",  1,  f_queue)  );  
        resume(  create(future_cons,  1024,  20,  "fcons7",  1,  f_queue)  );
        resume(  create(future_prod,  1024,  20,  "fprod3",  1,  f_queue)  );
        resume(  create(future_prod,  1024,  20,  "fprod4",  1,  f_queue)  );
        resume(  create(future_prod,  1024,  20,  "fprod5",  1,  f_queue)  );
        resume(  create(future_prod,  1024,  20,  "fprod6",  1,  f_queue)  );
		sleep(1);




		
        syscall exclusive = future_freemem(f_exclusive);
    	syscall shared = future_freemem(f_shared); 
		syscall queue = future_freemem(f_queue);
		if (!(exclusive == (uint32 *)OK && shared == (uint32 *)OK && queue == (uint32 *)OK))
		{
			printf("There is an error, please check\n");
		}
		else{
			printf("Success\n");
		}
	}
	return 0;
}
