#include "main.h"

/**
 * interpret_dollar - interprets dollar sign
 * @str: pointer to strings
 * @status: exit code
*/
void interpret_dollar(char **str, int status)
{
	char *new_str = NULL;
	int i = 1;

	while (str[i] != NULL)
	{
		if (str[i][0] == '$')
		{
			if (_strlen(str[i]) == 2)
			{
				if (str[i][1] == '?')
				{
					new_str = itostr(status);
					free(str[i]);
					str[i] = new_str;
				}
				else if (str[i][1] == '$')
				{
					new_str = itostr(getpid());
					free(str[i]);
					str[i] = new_str;
				}
			}
			else if (_strlen(str[i]) > 2)
			{
				new_str = _getenv(++(str[i]));

				str[i] = new_str;
			}
		}
		i++;
	}
}
