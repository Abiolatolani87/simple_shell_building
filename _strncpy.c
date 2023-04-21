#include "main.h"

/**
 * _strncpy - copy contents of one string to another string
 * @dest: pointer to the  string to be copied to
 * @src: pointer to the string to be copied
 * @n: number of string src to copy
 * Return: pointer to the resulting string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; *(src + i) != '\0' && i < n; i++)
		dest[i] = src[i];

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}