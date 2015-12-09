#include <ctype.h>
#include <prodcons.h>

/* --------------------------------------------------------------------------------------------------------------
 *  				xsh_netfutures.c   -  Use future for sending and reciving messages
 * ------------------------------------------------------------------------------------------------------------
 */

 #define SIZE 1024
 shellcmd xsh_netfutures(int nargs, char *args[]) {
 	future *f_exclusive;
	int	retval;
	char response[SIZE];
	uint32 target_ip, locport = 8000;

	/* Output info for '--help' argument */
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) 
	{
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tSends a message using futures\n");
		printf("Options (one per invocation):\n");		
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	/* Check argument count */
	/* If argument count is greater than 2, then there are too many arguments*/
	if (nargs > 2) 
	{
		fprintf(stderr, "%s: too many arguments\n", args[0]);
		return 1;
	}

	/* If argument count is less than 2, then there are too few arguments*/
	if (nargs < 2) 
	{
		fprintf(stderr, "%s: too few arguments\n", args[0]);
		return 1;
	}

	f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
	
	udp_init();
	int32 slot =0;
	dot2ip("192.168.1.100",&target_ip);
	
	/* register local UDP port */
	slot=udp_register(target_ip,8000,locport);
	if (slot == SYSERR) {
		fprintf(stderr, "%s: could not reserve UDP port %d\n",
				args[0], locport);
		return 1;
	}
	else
		kprintf("\nSlot obtained : %d\n",slot);

	resume (create (net_consumer, 1024, 20, "net_consumer", 1, f_exclusive));
	resume (create (net_producer, 1024, 20, "net_producer", 3, f_exclusive, slot, args[1]));
	return 0;
}