
#include <xinu.h>
#include <string.h>
#include <stdio.h>

shellcmd xsh_reset(int nargs, char *args[]) {
	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tPerforms a soft reset on the system.\n\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}

	if (nargs > 1)
	{
		kprintf("Too many arguments\n");
	}
	else {
	volatile uint32 *prm_rstctrl = (volatile uint32 *) 0x44E00F00; //Getting the address of the register
	*prm_rstctrl = 0x01; // Generate a warm software reset
	}
	return 0;
}