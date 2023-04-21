#include "main.h"

void handle_exit(int argv_count, char **argv)
{
	int exit_code = 0;

	if (argv_count > 2)
	{
		newputs("exit");
		newputs("bash: exit: ");
		newputs(argv[1]);
		_puts(": wrong argument count");
		exit(2);
	}
	else if (argv_count == 1)
	{
		_puts("exit");
		exit(0);
	}
	else
	{
		if (is_all_digits(argv[1]))
		{
			exit_code = _atoi(argv[1]);
			exit(exit_code);
		}
		else
		{
			_puts("exit");
			newputs("bash: exit: ");
			newputs(argv[1]);
			newputs(": numeric argument required");
			exit(2);
		}
	}
}