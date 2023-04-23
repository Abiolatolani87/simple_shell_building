#include "main.h"

/**
 * main - super simple shell
 * Return: Always 0
 */
int main(void)
{

	int status = 0;
	FILE *stream = stdin;
	char *line = NULL;
	size_t len = 0;
	ssize_t bytes_read = 0;
	char delim = ' ';
	char *builtin[] = {"exit", "setenv", "unsetenv", "cd", "getenv", NULL};
	list_t *head_arvg = NULL;
	char **argv = NULL;

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
