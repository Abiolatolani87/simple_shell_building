#include "main.h"

/**
 * handle_setenv - execute cd command
 * @argv_count: number of arguments
 * @argv: pointer to strings
 * @status: pointer to exit code
*/
void handle_setenv(int argv_count, char **argv, int *status)
{
	if (argv_count != 3)
	{
		/*fprintf(stderr, "%s:usage: %s VARIABLE VALUE\n", argv[0], argv[0]);*/
		*status = 127;
	}
	else
	{
		if ((setenv(argv[1], argv[2], 1)) == -1)
		{
			/*_puts("command invoked cannot execute");*/
			*status = 126;
		}
	}
	*status = 0;
}
