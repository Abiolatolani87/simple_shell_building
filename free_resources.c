#include "main.h"

void free_resources(char *line, list_t *head_argv, char **argv)
{
	if (line != NULL)
		free(line);
	if (head_argv != NULL)
		free_list(head_argv);
	if (argv != NULL)
		free(argv);
}