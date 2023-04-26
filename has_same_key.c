#include "main.h"

/**
 * has_same_key - checks if two keys are the same
 * @str: pointer to environment variable
 * @substr: pointer to a key
 * Return: 1 if same, 0 otherwise
 */

int has_same_key(char *str, const char *substr)
{
	unsigned int key_length = 0;
	unsigned int substr_length = (unsigned int)_strlen(substr);

	key_length = key_len(str);

	if (key_length != substr_length)
		return (0);

	while (*str != '=')
	{
		if (*str != *substr)
			return (0);
		str++;
		substr++;
	}
	return (1);
}
