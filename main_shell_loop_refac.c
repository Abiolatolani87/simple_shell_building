#include "main.h"

void readline(char **line, FILE *stream, size_t *len, ssize_t *bytes);
void handle_parsed_line(char ***tokens, FILE *stream, int *status);
void handle_parse_error(char *str, int *status);
void handle_parsed_cmd(char *str, FILE *stream, int *status);

/**
 * main - super simple shell
 * @ac: argument's count
 * @av: argument's values
 * Return: Always 0
 */
int main(int ac, char **av)
{

	int status = 0, i = 0, j = 0, k = 0;
	FILE *stream = stdin;
	char *line = NULL;
	size_t len = 0;
	ssize_t bytes_read = 0;
	list_t *head_main = NULL;
	char **strs_split_by_semicolon = NULL;

	argc = ac;
	argv = av;

	while (1)
	{
		prompt_user();
		readline(&line, stream, &len, &bytes_read);

		if (line == NULL || *line == '#' || *line == '\n' || bytes_read == 0)
			continue;

		trunc_comment(line);

		strs_split_by_semicolon = parse_semicolon(line, &status, head_main);

		if (!strs_split_by_semicolon || !*strs_split_by_semicolon)
		{
			handle_parse_error(av[0], &status);
			continue;
		}
		handle_parsed_line(&strs_split_by_semicolon, stream, &status);

		free_list(head_main);
	}
	free(line);
	fclose(stream);

	return (0);
}

/**
 * readline - read line
 * @line: pointer to pointer to line
 * @stream: input stream
 * @len: length of line
 * @bytes: number of bytes read
*/
void readline(char **line, FILE *stream, size_t *len, ssize_t *bytes)
{
	*bytes = getline(line, len, stream);
	if (*bytes == -1)
	{
		_putchar('\n');
		free(*line);
		exit(1);
	}
}

/**
 * handle_parse_error - handle error
 * @str: pointer to string
 * @status: pointer to exit code
*/
void handle_parse_error(char *str, int *status)
{
	newputs(str);
	_puts(": Could not parse command");
	*status = 127;
}

/**
 * handle_parsed_line - process tokens separated by semicolon
 * @tokens: holds address of of array of tokens
 * @stream: input stream
 * @status: pointer to exit code
*/
void handle_parsed_line(char ***tokens, FILE *stream, int *status)
{
	int i = 0, j = 0, k = 0;

	cmd_ops *ptr_to_cmd_ops = NULL;

	while (*tokens[i] != NULL)
	{
		if (contains_log_operator(*tokens[i]))
		{
			ptr_to_cmd_ops = parse_logical_ops(*tokens[i], status);

			if (!ptr_to_cmd_ops || !ptr_to_cmd_ops->cmd_tokens ||
			    !*(ptr_to_cmd_ops->cmd_tokens))
			{
				handle_parse_error(argv[0], &status);
				break;
			}
			j = 0;
			k = 0;
			while (ptr_to_cmd_ops->cmd_tokens[j] != NULL)
			{
				handle_parsed_cmd(ptr_to_cmd_ops->cmd_tokens[j], stream, status);

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
			handle_parsed_cmd(*tokens[i], stream, status);
		}

		i++;
	}
}

/**
 * handle_parsed_cmd - split commands by space and execute
 * @str: pointer to string to tokenize
 * @stream: input stream
 * @status: pointer to exit code
*/
void handle_parsed_cmd(char *str, FILE *stream, int *status)
{
	char delim = ' ';
	char **cmds = NULL;
	list_t *head_arvg = NULL;
	char *builtin[] = {"exit", "setenv", "unsetenv", "cd", "getenv", NULL};

	cmds = str_into_tokens(str, delim, head_arvg);

	if (built_in(cmds[0], builtin))
	{
		execute_builtin_cmd(cmds, status, str, head_arvg, stream);
	}
	else
	{
		create_child_process(status, cmds);
	}
	free_list(head_arvg);
	free(cmds);
}