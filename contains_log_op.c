#include "main.h"

/**
 * contains_log_op - checks if string contains a logical operator
 * @str: string to be checked
 * Return: 1 if true, else return 0
*/

int contains_log_operator(char *str)
{
        int i = 0;

        while(str[i] != '\0')
        {
                if((str[i] == '&' && str[i + 1] == '&') || (str[i] == '|' && str[i + 1] == '|'))
                        return (1);

                i++;
        }
        return (0);
}