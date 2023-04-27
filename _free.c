#include "main.h"

/**
 * _free: free allocated memory
 * @s: pointer to memory to free
*/
void _free(char *s)
{
	if (s)
		free(s);
}
