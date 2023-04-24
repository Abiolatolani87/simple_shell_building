#include "main.h"

/**
 * trunc_comment - truncates everything after the #
 * @str: string to be truncated of the comment section
*/

void trunc_comment(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '#')
			str[i] = '\0';
		i++;
	}
}
