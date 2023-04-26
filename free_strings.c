#include "main.h"

/**
 * free_strings - deallocates memory
 * @s: strings to free
*/
void free_strings(char **s)
{
	int i = 0;

	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
}
