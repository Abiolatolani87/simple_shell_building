#include "main.h"

void execute_builtin_cmd(char **argv, int *status,
			 list_t *head_argv, FILE *stream, char ***tokens)
{
	int argv_count = 0;

	argv_count = count_strs(argv);
	if (_strcmp(argv[0], "exit") == 0)
	{
		handle_exit(argv_count, argv, head_argv, stream, tokens);
	}
	else if (_strcmp(argv[0], "setenv") == 0)
	{
		handle_setenv(argv_count, argv, status);
	}
	else if (_strcmp(argv[0], "unsetenv") == 0)
	{
		handle_unsetenv(argv_count, argv, status);
	}
	else if (_strcmp(argv[0], "cd") == 0)
	{
		handle_cd(argv_count, argv, status);
	}
	else if (_strcmp(argv[0], "getenv") == 0)
	{
		/*printf("%s: %s\n", argv[1], _getenv(argv[1]));*/
		newputs(argv[1]);
		newputs(": ");
		_puts(_getenv(argv[1]));
	}
}
