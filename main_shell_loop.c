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
		if (line == NULL || *line == '\n')
			continue;

		strs_split_by_semicolon = parse_semicolon(line, &status, head_main);
		if (!strs_split_by_semicolon || !*strs_split_by_semicolon)
		{
			newputs(av[0]);
			_puts(": Could not parse command");
			status = 127;
			continue;
		}
		while (strs_split_by_semicolon[i] != NULL)
		{
			ptr_to_cmd_ops = parse_logical_ops(strs_split_by_semicolon[i], &status);

			if (!ptr_to_cmd_ops || !ptr_to_cmd_ops->cmd_tokens || !*(ptr_to_cmd_ops->cmd_tokens))
			{
				newputs(av[0]);
				_puts(": Could not parse command");
				status = 127;
				break;
			}
			while (*ptr_to_cmd_ops->cmd_tokens != NULL)
			{
				printf("str: %s\n", *(ptr_to_cmd_ops->cmd_tokens)++);
			}
			while (*ptr_to_cmd_ops->ops_tokens != NULL)
			{
				printf("str: %s\n", *(ptr_to_cmd_ops->ops_tokens)++);
			}

			i++;
		}
		return (1);

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
	}
	free(line);
	fclose(stream);

	return (0);
}
