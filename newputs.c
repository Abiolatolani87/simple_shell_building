#include "main.h"

/**
 * newputs - prints the given string without new line
 * @str: pointer to the string to be printed
 */

void newputs(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str);
		str++;
	}
}
