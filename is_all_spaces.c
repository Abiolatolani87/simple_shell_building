#include "main.h"

/**
 * is_only_spaces - checks if string has only spaces
 * @s: pointer to string to check
 * Return: 1 if string has all spaces, 0 otherwise
 */
int is_only_spaces(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		if (!isspace(s[i]))
			return (0);
	return (1);
}
