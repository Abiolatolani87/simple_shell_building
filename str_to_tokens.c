#include "main.h"

/**
 * str_into_tokens - creates a list that stores each token in a node
 * then creates an array of pointers to each spot in the array
 * @str: string to be tokenised
 * @delim: delimeter used to separate the strings
 * @head: pointe to head of list storing tokens
 * Return: NULL on failure, else return ppointer to array holding pointers to array
*/

char **str_into_tokens(const char *str, char delim, list_t *head)
{
	char buffer[1024] = {0};
	int i = 0;

	if (!str)
		return (NULL);

	while (*str != '\0')
	{
		while (*str == delim)
			str++;

		if (*str == '\0' || *str == '\n')
			break;

		while (*str != delim && *str != '\0' && *str != '\n')
		{
			buffer[i] = *str;
			str++;
			i++;
		}
		buffer[i] = '\0';
		add_node_end(&head, buffer);
		i = 0;
	}

	int list_length = list_len(head);
	char **ptr_to_tokens = malloc(sizeof(char *) * (list_length + 1));
	ptr_to_tokens = store_str_ptrs(head, ptr_to_tokens);
	
	return (ptr_to_tokens);
}