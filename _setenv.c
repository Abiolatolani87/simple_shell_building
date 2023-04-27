#include "main.h"

/**
 * _setenv - sets the value of given env variable to value specified by user
 * @name: name of environment variable to be set
 * @value: value to which environment variable must be set
 * @overwrite: if set to 1 overwrite value already stored in variable
 * otherwise if set to 0 leave variable as is and dont change
 * Return: -1 on failure, else return 0
*/

int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0, environ_count = count_strs(environ);
	char *new_env_str = NULL;
	char **new_environ = NULL;
	int new_env_var_len = _strlen(name) + _strlen(value) + 2;

	if (!name || !value)
		return (-1);
	new_env_str = malloc(new_env_var_len);
	if (!new_env_str)
		return (-1);
	_strcat(new_env_str, name);
	_strcat(new_env_str, "=");
	_strcat(new_env_str, value);
	while (environ[i])
	{
		if (strncmp(environ[i], name, _strlen(name)) == 0)
		{
			if (!overwrite)
			{
				free(new_env_str);
				return (0);
			}
			strncpy(environ[i], new_env_str, new_env_var_len);
			free(new_env_str);
			return (0);
		}
		i++;
	}
	new_environ = malloc(sizeof(char *) * (environ_count + 2));
	i = 0;
	while (environ[i] != NULL)
	{
		new_environ[i] = environ[i];
		i++;
	}
	if (!new_environ)
		return (-1);
	environ = new_environ;
	environ[environ_count] = new_env_str;
	environ[environ_count + 1] = NULL;

	return (0);
}
