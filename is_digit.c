#include "main.h"

/**
 * is_all_digits - check if string contains only digits
 * @s: pointer to string to check
 * Return: 1 if only digits, 0 otherwise
 */
int is_all_digits(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
	{
		if (!isdigit(*(s + i)))
			return (0);
		i++;
	}
	return (1);
}
