#include "main.h"

/**
 * path_list -  fetches the path from environment variable
 * Return: head of list storing path
*/

list_t *path_list()
{
	int index = 0;
	char buffer[512];
	list_t *head = NULL;
	char *value = _getenv("PATH");

	while (*value != '\0')
	{
		if (*value == ':')
		{
			buffer[index] = '\0';
			/* create a node for the string in the buffer */
			add_node(&head, buffer);
			index = -1;
		}
		else
		{
			buffer[index] = *value;
		}
		value++;
		index++;
	}
	buffer[index] = '\0';
	/* create a node for the string in the buffer */
	add_node(&head, buffer);

	return (head);
}