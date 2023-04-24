#include "main.h"

/**
 * has_forward_slash - checks if string contains a forward slash
 * @str: string to be checked for forward slash
 * Return: 1 if str contains a /, otherwise return 0
*/

int has_forward_slash(char *str)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}
