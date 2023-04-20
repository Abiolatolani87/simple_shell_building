#include "main.h"

/*1. Tokenise
2. check the first character of each  token for $
    2.1  if it has $ sign (check length = 2)
            check next char
                if = ?
                    (replace $? with exit status)
                 else if ($)
                    (replace $$ with pid)
    2.2  else != 2 call getenv()
            (replace getenv with value/result)

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
				if (str[i][0] == '?')
				{
					new_str = itostr(status);
					free(str[i]);
					str[i] = new_str;
				}
				else if (str[i][0] == '$')
				{
					new_str = itostr(getpid());
					free(str[i]);
					str[i] = new_str;
				}
			}
			else if (_strlen(str[i]) > 2)
			{
				new_str = _getenv(++(str[i]));
				//free(str[i]);
				str[i] = new_str;
			}
		}
		i++;
	}
}