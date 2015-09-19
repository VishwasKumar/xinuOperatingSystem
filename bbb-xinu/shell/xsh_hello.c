/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xhs_hello - write argument strings to stdout with hello
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs, char *args[]) {
	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s\n\n", args[0]);
		printf("Description:\n");
		printf("\tWrite arguments to the standard output.\n\n");
		printf("\tDisplay the ARG, with message Hello <ARG>. Welcome to the world of Xinu!\
 	and followed by a newline, on the standard output.\n");
		printf("\t--help\tdisplay this help and exit\n");
		return 0;
	}
	if (nargs < 2)
		printf("Too few arguments\n");
	else if (nargs > 2)
		printf("Too many arguments\n");
	else
		printf("Hello %s, Welcome to the world of Xinu!!\n", args[1]);
	return 0;
}
