#include "main.h"

/**
 * end_with_forward_slash - checks if a string ends with a forward slash
 * @str: string to be checked for ending eith /
 * Return: 1 if string ends with forward slash, else return 0
*/

int end_with_forward_slash(char *str)
{
	if (!str)
		return (0);
	/* check if last character in str is '/' */
	return (str[strlen(str) - 1] == '/');
}