#include "main.h"

/**
 * count_args - arguments count
 * Return: number of arguments
*/
int count_args(char **args)
{
	int i = 0;
	if (!args || !*args)
		return (0);

	while (args[i] != NULL)
	{
		i++;
	}
	return (i);
}
