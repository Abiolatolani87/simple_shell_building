#include "main.h"

/**
 * _getenv - gets an environment variable
 * @name: pointer to name of variable
 * Return: pointer to environment variable
 */

char *_getenv(const char *name)
{
	char *value = NULL;
	unsigned int i = 0;

	while (environ[i] != NULL)
	{
		if (has_same_key(environ[i], name))
			value = get_value(environ[i]);
		i++;
	}
	return (value);
}