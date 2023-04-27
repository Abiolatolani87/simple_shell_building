#include "main.h"

/**
 * _unsetenv - sets value of environment variable to Zero
 * @name: name of environment variable to unset
 * Return: 0 if successfully unset, otherwise return -1
*/

int _unsetenv(const char *name)
{
	int found = 0, i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], name, _strlen(name)) == 0)
		{
			_free(environ[i]);
			found = 1;
			break;
		}
		i++;
	}
	if (found)
	{
		/* Move remaining environment variables back by 1 */
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
		return (0);
	}
	else
		return (-1);
}
