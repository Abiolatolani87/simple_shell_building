#include "main.h"

/**
 * handle_unsetenv - execute cd command
 * @argv_count: number of arguments
 * @argv: pointer to strings
 * @status: pointer to exit code
*/
void handle_unsetenv(int argv_count, char **argv, int *status)
{
	if (argv_count != 2)
	{
		/*fprintf(stderr, "%s:usage: %s VARIABLE\n", argv[0], argv[0]);*/
		newputs(argv[0]);
		newputs(":usage: ");
		_puts(argv[0]);
		*status = 127;
	}
	else
	{
		if ((_unsetenv(argv[1])) == -1)
		{
			_puts("command invoked cannot execute");
			*status = 126;
		}
	}
	*status = 0;
}
