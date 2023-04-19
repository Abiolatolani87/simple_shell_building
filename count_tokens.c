#include "main.h"

/**
 * count_strs - count strings in array
 * @strs: array to be counted
 * Return: number of strings in array
*/

int count_strs(char **strs)
{
	int i = 0;

	while (strs[i] != NULL)
	{
		i++;
	}
        return (i);
}