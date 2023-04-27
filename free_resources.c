#include "main.h"

/**
 * free_resources - free memory
 * @head_argv: pointer to list to free
 * @argv: pointer to strings to free
 * @stream: pointer to file stream
*/
void free_resources(list_t *head_argv, char **argv, FILE *stream)
{
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
