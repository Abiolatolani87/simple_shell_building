#include "main.h"

/**
 * built-in - checks whether command is a built in
 * @str: string to be checked
 Return: 1 if yes, 0 if no
*/

int built_in(char *str, char **builtin)
{
    int i = 0;

    while(builtin[i] != NULL)
    {
       if ((_strcmp(builtin[i], str)) == 0)
       {
            return (1);
       }

        i++;
    }

    return (0);
}
