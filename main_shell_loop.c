#include "main.h"

/**
 * main - super simple shell
 * Return: Always 0
 */
int main(int ac, char **av)
{

	int status = 0, i = 0;
	FILE *stream = stdin;
	char *line = NULL;
	size_t len = 0;
	ssize_t bytes_read = 0;
	char delim = ' ';
	char *builtin[] = {"exit", "setenv", "unsetenv", "cd", "getenv", NULL};
	list_t *head_arvg = NULL, *head_main = NULL;
	char **argv = NULL, **strs_split_by_semicolon = NULL;
	cmd_ops *ptr_to_cmd_ops = NULL;

	(void)ac;

	while (1)
	{
		prompt_user();

		if ((bytes_read = getline(&line, &len, stream)) == -1)
		{
			_putchar('\n');
			exit(1);
		}

		if (line == NULL || *line == '\n') // check that string holding getline input is valid
			continue;

		strs_split_by_semicolon = parse_semicolon(line, &status, head_main);

		printf("string: %s", strs_split_by_semicolon[i]);

		if (!strs_split_by_semicolon || !*strs_split_by_semicolon)	     // checks that above assignment was successfully executed
		{
			newputs(av[0]);
			_puts(": Could not parse command");
			status = 127;
			continue;
		}
		printf("line: %s", line);
		while (strs_split_by_semicolon[i] != NULL)
		{
			printf("string split %s\n", strs_split_by_semicolon[i]);
			if (contains_log_operator(strs_split_by_semicolon[i]))
			{
				ptr_to_cmd_ops = parse_logical_ops(strs_split_by_semicolon[i], &status); // split by logical operators, return pointer to list

				if (!ptr_to_cmd_ops || !ptr_to_cmd_ops->cmd_tokens || !*(ptr_to_cmd_ops->cmd_tokens))
				{
					newputs(av[0]);
					_puts(": Could not parse command");
					status = 127;
					break;
				}
				while (*ptr_to_cmd_ops->cmd_tokens != NULL)
				{
					argv = str_into_tokens(line, delim, head_arvg);

					if (built_in(argv[0], builtin))
					{
						execute_builtin_cmd(argv, &status, line, head_arvg, stream);
					}
					else
					{
						create_child_process(&status, argv);
					}
					free_list(head_arvg);
					free(argv);
					if (status == 0)
					{
						if (_strcmp(*ptr_to_cmd_ops->ops_tokens, "&&") == 0)
							continue;
						else if (_strcmp(*ptr_to_cmd_ops->ops_tokens, "||") == 0)
							break;
						else
							exit(1);
					}
					else
					{
						if (_strcmp(*ptr_to_cmd_ops->ops_tokens, "&&") == 0)
							break;
						else if (_strcmp(*ptr_to_cmd_ops->ops_tokens, "||") == 0)
							continue;
						else
							exit(1);
					}

				}
			}
			else
			{
				argv = str_into_tokens(line, delim, head_arvg); // continue with normal execution

				if (built_in(argv[0], builtin))
				{
					execute_builtin_cmd(argv, &status, line, head_arvg, stream);
				}
				else
				{
					create_child_process(&status, argv);
				}
				free_list(head_arvg);
				free(argv);
			}

			i++;
		}
		free_list(head_main);
	}
	free(line);
	fclose(stream);

	return (0);
}
