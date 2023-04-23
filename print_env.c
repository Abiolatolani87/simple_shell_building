#include "main.h"

/**
 * print_env - prints the keys and values of environmennt variables
 */

void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		/*printf("%s\n", environ[i]);*/
		_puts(environ[i]);
		i++;
	}
}