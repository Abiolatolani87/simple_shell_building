#include "main.h"

/**
 * get_value - get a pointer to start of an environment variable's value
 * @str: pointer to environment variable
 * Return: pointer to start of value
 */

char *get_value(char *str)
{
	while (*str != '=')
	{
		str++;
	}
	/* Point to next character after = */
	str++;

	return (str);
}
