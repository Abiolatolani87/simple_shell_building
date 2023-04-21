#include "main.h"

/**
 * key_len - calculated length of environment variable's key
 * @str: pointer to environment variable
 * Return: length of key
 */

unsigned int key_len(char *str)
{
	unsigned int len = 0;

	while (*str != '=')
	{
		len++;
		str++;
	}
	return (len);
}