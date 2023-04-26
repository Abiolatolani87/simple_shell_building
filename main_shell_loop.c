#include "main.h"

void readline(char **line, FILE **stream, size_t *len, ssize_t *bytes);
void handle_parsed_line(char ***tokens, FILE *stream,
			int *statusint, char *shell_name);
void handle_parse_error(char *str, int *status);
void handle_parsed_cmd(char ***tokens, char *str, FILE *stream, int *status);
void execute_cmds_with_ops(cmd_ops *ptr_to_cmd_ops, FILE *stream, int *status);
void callback(int signum);
char **argvalues;
char *line = NULL;
/**
 * main - super simple shell
 * @ac: argument's count
 * @av: argument's values
 * Return: Always 0
 */
int main(int ac, char **av)
{
	int status = 0;
	FILE *stream = stdin;
	size_t len = 0;
	ssize_t bytes_read = 0;
	list_t *head_main = NULL;
	char **strs_split_by_semicolon = NULL;

	argvalues = av;
	(void)ac;
	while (1)
	{
		signal(SIGINT, callback);
		if (isatty(fileno(stdin)))
			prompt_user();
		readline(&line, &stream, &len, &bytes_read);

		if (line == NULL || is_only_spaces(line) || *line == '#' || *line == '\n' || bytes_read == 0)
			continue;
		trunc_comment(line);
		strs_split_by_semicolon = parse_semicolon(line, head_main);

		if (!strs_split_by_semicolon || !*strs_split_by_semicolon)
		{
			handle_parse_error(av[0], &status);
			continue;
		}
		handle_parsed_line(&strs_split_by_semicolon, stream, &status, av[0]);

		free_list(head_main);
	}

	printf("after typing exit\n");
	return (0);
}

/**
 * callback - callback function
 * @signum: signal number
*/
void callback(int signum)
{
	newputs("\n$ ");
	(void)signum;
}

/**
 * readline - read line
 * @line: pointer to pointer to line
 * @stream: input stream
 * @len: length of line
 * @bytes: number of bytes read
 */
void readline(char **line, FILE **stream, size_t *len, ssize_t *bytes)
{
	*bytes = getline(line, len, *stream);
	if (*bytes == -1)
	{
		if (isatty(fileno(stdin)))
		{
			custom_print(2, "\n");
			free(*line);
		}
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
	custom_print(2, ":%s Could not parse command\n", str);
	*status = 127;
}

/**
 * handle_parsed_line - process tokens separated by semicolon
 * @tokens: holds address of of array of tokens
 * @stream: input stream
 * @status: pointer to exit code
 * @shell_name: program name
 */
void handle_parsed_line(char ***tokens, FILE *stream,
			int *status, char *shell_name)
{
	int i = 0;

	cmd_ops *ptr_to_cmd_ops = NULL;

	while ((*tokens)[i] != NULL)
	{
		if (contains_log_operator((*tokens)[i]))
		{
			ptr_to_cmd_ops = parse_logical_ops((*tokens)[i]);

			if (!ptr_to_cmd_ops || !ptr_to_cmd_ops->cmd_tokens ||
			    !ptr_to_cmd_ops->cmd_tokens[0])
			{
				handle_parse_error(shell_name, status);
				break;
			}
			execute_cmds_with_ops(ptr_to_cmd_ops, stream, status);
		}
		else
			handle_parsed_cmd(tokens, (*tokens)[i], stream, status);
		i++;
	}
	free_strings(*tokens);
}

/**
 * handle_parsed_cmd - split commands by space and execute
 * @str: pointer to string to tokenize
 * @stream: input stream
 * @status: pointer to exit code
 */
void handle_parsed_cmd(char ***tokens, char *str, FILE *stream, int *status)
{
	char delim = ' ';
	char **cmds = NULL;
	list_t *head_arvg = NULL;
	char *builtin[] = {"exit", "setenv", "unsetenv", "cd", "getenv", NULL};

	cmds = str_into_tokens(str, delim, head_arvg);

	if (built_in(cmds[0], builtin))
	{
		execute_builtin_cmd(cmds, status, head_arvg, stream, tokens);
	}
	else
	{
		create_child_process(status, cmds);
	}
	free_list(head_arvg);
	free_strings(cmds);
}

/**
 * execute_cmds_with_ops - split commands by space and execute
 * @ptr_to_cmd_ops: pointer to struct holding array of cmds and ops
 * @stream: input stream
 * @status: pointer to exit code
 */
void execute_cmds_with_ops(cmd_ops *ptr_to_cmd_ops, FILE *stream, int *status)
{
	int j = 0, k = 0;

	while (ptr_to_cmd_ops->cmd_tokens[j] != NULL)
	{
		handle_parsed_cmd(&(ptr_to_cmd_ops->cmd_tokens), ptr_to_cmd_ops->cmd_tokens[j], stream, status);
		j++;
		if (ptr_to_cmd_ops->ops_tokens[k] == NULL)
			break;

		if (*status == 0)
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
