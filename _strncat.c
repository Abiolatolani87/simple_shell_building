#include "main.h"

/**
 * _strncat - concatenates two strings
 * @dest: pointer to the  string to be added onto
 * @src: pointer to the string to add on
 * @n: number of src string to concatenate
 * Return: pointer to the resulting string
 */

char *_strncat(char *dest, char *src, int n)
{
	int len = _strlen(dest);
	int i;

	for (i = 0; *(src + i) != '\0' && i < n; i++)
		dest[len + i] = src[i];
	dest[len + i] = '\0';

	return (dest);
}
