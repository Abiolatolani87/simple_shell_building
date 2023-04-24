#include "main.h"

/**
 * path_exist - check if path exists
 * @str: pointer to string to check
 * Return: 0
 */

int path_exist(const char *str)
{
	struct stat st;

	return (stat(str, &st) == 0);
}
