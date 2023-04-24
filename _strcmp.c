#include "main.h"

/**
 * _strcmp - compares two strings
 * @s1: pointer to first string to be compared
 * @s2: pointer to second string to be compared
 * Return: neg value if s1 < s2, 0 if s1 = s2, pos value if s1 > s2
 */

int _strcmp(char *s1, char *s2)
{
	int i;
	int same = 0;
	int s1_len = _strlen(s1);
	int s2_len = _strlen(s2);

	if (s1_len != s2_len)
	{
		return (1);
	}

	for (i = 0; i < s1_len; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (same);
}
