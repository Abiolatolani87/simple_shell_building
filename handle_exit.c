#include "main.h"

/**
 * handle_exit - execute exit builtin
 * @argv_count: number of arguments
 * @argv: pointer to strings
 * @head_argv: pointer to list
 * @stream: pointer to input stream
 * @tokens: holds address of of array of tokens
*/
void handle_exit(int argv_count, char **argv,
		 list_t *head_argv, FILE *stream, char ***tokens)
{
	int exit_code = 0;

	if (argv_count > 2)
	{
		custom_print(2, "exit\nbash: exit: %s: wrong argument count", argv[1]);
		exit(2);
	}
	else if (argv_count == 1)
	{
		custom_print(2, "exit\n");
		free_resources(head_argv, argv, stream);
		free_strings(*tokens);
		free(line);
		exit(0);
	}
	else
	{
		if (is_all_digits(argv[1]))
		{
			exit_code = _atoi(argv[1]);
			free_resources(head_argv, argv, stream);
			free_strings(*tokens);
			free(line);
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
