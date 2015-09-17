/* xsh_hello.c - xsh_hello */

#include <xinu.h>
#include <string.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xhs_hello - write argument strings to stdout with hello
 *------------------------------------------------------------------------
 */

shellcmd xsh_hello(int nargs, char *args[]) {

	int32	i;			/* walks through args array	*/

	if (nargs > 2 )
		printf("Too many arguments\n");
        else if(nargs < 2)
                printf("Too few arguments")
	 else
		printf("Hello %s, Welcome to the world of Xinu!!\n", args[1]);
	return 0;
}
