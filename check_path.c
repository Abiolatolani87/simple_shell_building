#include "main.h"

/**
 * check_path - checks if there is a built in function for given command
 * by checking if the path with command added exist
 * @first_arg: first argument fetched from the command line
 * @dirs: directory paths added to first command
 * @head: pointer to list holding
 *Return: NULL if fail, else return the full file path
*/

char *check_path(char *first_arg, char **dirs, list_t *head)
{
	if (has_forward_slash(first_arg))
	{
		if (end_with_forward_slash(first_arg))
			return (NULL);
		else
		{
			if (path_exist(first_arg))
				return (first_arg);
			else
				return (NULL);
		}
	}
	else
	{
		char *path = _getenv("PATH");
		dirs = str_into_tokens(path, ':', head);

		int i = 0;
		int length = strlen(first_arg);
		char *file_fullpath = NULL;

		while (dirs[i] != NULL)
		{
			dirs[i] = realloc(dirs[i], strlen(dirs[i]) + length + 2);

			strcat(dirs[i], "/");
			strcat(dirs[i], first_arg);

			if (path_exist(dirs[i]))
			{
				file_fullpath = strdup(dirs[i]);
				return (file_fullpath);
			}

			i++;
		}
		return (NULL);
	}
