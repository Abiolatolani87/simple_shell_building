#include "main.h"

/**
 * main - super simple shell
 * Return: Always 0
 */
int main(int ac, char **av)
{

	int status = 0, i = 0, j = 0, k = 0;
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
			free(line);
			exit(1);
		}

		if (*line == '#' || line == NULL || *line == '\n')
			continue;

		trunc_comment(line);

		strs_split_by_semicolon = parse_semicolon(line, head_main);

		if (!strs_split_by_semicolon || !*strs_split_by_semicolon)
		{
			newputs(av[0]);
			_puts(": Could not parse command");
			status = 127;
			continue;
		}

		i = 0;
		while (strs_split_by_semicolon[i] != NULL)
		{
			if (contains_log_operator(strs_split_by_semicolon[i]))
			{
				ptr_to_cmd_ops = parse_logical_ops(strs_split_by_semicolon[i]);

				if (!ptr_to_cmd_ops || !ptr_to_cmd_ops->cmd_tokens || !*(ptr_to_cmd_ops->cmd_tokens))
				{
					newputs(av[0]);
					_puts(": Could not parse command");
					status = 127;
					break;
				}
				j = 0;
				k = 0;
				while (ptr_to_cmd_ops->cmd_tokens[j] != NULL)
				{
					/* DISABLE ARGV EXTERN IN HEADER TO RUN THIS!!!!*/
					argv = str_into_tokens(ptr_to_cmd_ops->cmd_tokens[j], delim, head_arvg);

					if (built_in(argv[0], builtin))
					{
						execute_builtin_cmd(argv, &status, ptr_to_cmd_ops->cmd_tokens[j], head_arvg, stream);
					}
					else
					{
						create_child_process(&status, argv);
					}
					free_list(head_arvg);
					free(argv);
					j++;
					if (ptr_to_cmd_ops->ops_tokens[k] == NULL)
						break;

					if (status == 0)
					{
						if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "&&") == 0)
						{
							k++;
							continue;
						}
						else if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "||") == 0)
						{
							k++;
							break;
						}
						else
							exit(1);
					}
					else
					{
						if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "&&") == 0)
						{
							k++;
							break;
						}
						else if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "||") == 0)
						{
							k++;
							continue;
						}
						else
							exit(1);
					}
				}
			}
			else
			{
				argv = str_into_tokens(strs_split_by_semicolon[i], delim, head_arvg);

				if (built_in(argv[0], builtin))
				{
					execute_builtin_cmd(argv, &status, strs_split_by_semicolon[i], head_arvg, stream);
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
