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
		{
			if (i != 0 && !isspace(str[i - 1]))
				return;
			str[i] = '\0';
		}
		i++;
	}
}
