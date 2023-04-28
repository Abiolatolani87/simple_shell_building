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
		free_all(argv, head_argv, stream, tokens, 2);
	}
	else if (argv_count == 1)
	{
		/*custom_print(2, "exit\n");*/
		free_all(argv, head_argv, stream, tokens, 0);
	}
	else
	{
		if (is_all_digits(argv[1]))
		{
			exit_code = _atoi(argv[1]);
			free_all(argv, head_argv, stream, tokens, exit_code);
		}
		else
		{
			custom_print(2, "%s: %d: %s: Illegal number: %s\n",
				     argvalues[0], argv_count, argv[0], argv[1]);
			free_all(argv, head_argv, stream, tokens, 2);
		}
	}
}

/**
 * free_all - execute exit builtin
 * @argv: pointer to strings
 * @head_argv: pointer to list
 * @stream: pointer to input stream
 * @tokens: holds address of of array of tokens
 * @exit_code: exit code
*/
void free_all(char **argv, list_t *head_argv, FILE *stream,
	      char ***tokens, int exit_code)
{
	free_resources(head_argv, argv, stream);
	free_strings(*tokens);
	free(line);
	exit(exit_code);
}
