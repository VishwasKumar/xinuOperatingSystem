#include <xinu.h>
#include <stdio.h>
#include <string.h>

syscall printStackSpace();
void stackchecker();

shellcmd xsh_checkStack(int nargs, char *args[]){
		if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("use: %s \n\n", args[0]);
		printf("Description:\n");
		printf("\tDisplays the current memory use\n");
		printf("Options:\n");
		printf("\t--help\t\tdisplay this help and exit\n");
		return 0;
	}

	if (nargs > 1) {
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n",
				args[0]);
		return 1;
	}

	resume( create(stackchecker, 8, 20, "stackchecker", 0) );
	
}

void stackchecker(){
	syscall stkflag = printStackSpace(getpid());
	if (stkflag == (uint32 *) SYSERR)
		printf("There is an error, please check");
	int32 test, test1, test2, test3, test4 = 0;
	printf("(0x%08x) \n",&test);
	printf("(0x%08x) \n",&test1);
	printf("(0x%08x) \n",&test2);
	printf("(0x%08x) \n",&test3);
	printf("(0x%08x) \n",&test4);
	stkflag = printStackSpace(getpid());
	if (stkflag == (uint32 *) SYSERR)
		printf("There is an error, please check");
	
}


syscall printStackSpace(pid32 pid)
{
	intmask im = disable();
	struct procent *ptr = &proctab[pid];
	uint32 stackLen = 0;		/* Total used stack memory	*/
	uint32 stackBase = 0;
	uint32 size = 0;
	/* Calculate amount of allocated stack memory */
	/*  Skip the NULL process since it has a private stack */

	if (isbadpid(pid) || (pid == NULLPROC) || ptr->prstate == PR_FREE) {
		restore(im);
		return SYSERR;
	}

	stackLen = (uint32)proctab[pid].prstkptr;
	stackBase = (uint32)proctab[pid].prstkbase;
	size = stackBase - stackLen;

	/* Output statistics on current memory use */

	printf("Current system memory statistics:\n");
	printf("---------------------------------\n");
	printf("Base address: (0x%08x)\n", stackBase);
	printf("%10d bytes (0x%08x) of allocated stack space\n", stackLen, stackLen);
	printf("Size: %10d\n", size);
	restore(im);
	return OK;
}
