#include "main.h"

/**
 * free_resources - free memory
 * @line: pointer to line to free
 * @head_argv: pointer to list to free
 * @argv: pointer to strings to free
 * @stream: pointer to file stream
*/
void free_resources(char *line, list_t *head_argv, char **argv, FILE *stream)
{
	if (line != NULL)
		free(line);
	if (head_argv != NULL)
		free_list(head_argv);
	if (argv != NULL)
	{
		int i = 0;

		while (argv[i] != NULL)
		{
			free(argv[i]);
			i++;
		}
		free(argv[i]);
		free(argv);
	}
	fclose(stream);
}
