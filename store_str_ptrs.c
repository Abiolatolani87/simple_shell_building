#include "main.h"

/**
 * store_str_ptrs - store the addresses of all strings in the list
 * @h: pointer to a list
 * @ptrs_to_str: pointer to strings
 * Return: array of pointers to string
 */

char **store_str_ptrs(const list_t *h, char **ptrs_to_str)
{
	int i = 0;

	if (!h)
		return (NULL);

	while (h)
	{
		if (h->str)
		{
			ptrs_to_str[i] = _strdup(h->str);
			i++;
		}

		h = h->next;
	}
	ptrs_to_str[i] = NULL;

	return (ptrs_to_str);
}
