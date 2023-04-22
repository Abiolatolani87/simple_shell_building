#include "main.h"

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