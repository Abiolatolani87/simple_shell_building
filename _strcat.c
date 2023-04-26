#include "main.h"

/**
 * _strcat - concatenates two strings
 * @dest: pointer to the  string to be added onto
 * @src: pointer to the string to add on
 * Return: pointer to the resulting string
 */

char *_strcat(char *dest, const char *src)
{
	int len = _strlen(dest);
	int i;

	for (i = 0; *(src + i) != '\0'; i++)
		dest[len + i] = src[i];
	dest[len + i] = '\0';

	return (dest);
}
