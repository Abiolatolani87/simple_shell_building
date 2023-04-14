#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct list_s - singly linked list
 * @str: string - (malloc'ed string)
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

extern char **environ;

size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
list_t *add_node(list_t **head, const char *str);
list_t *add_node_end(list_t **head, const char *str);
void free_list(list_t *head);
char *_getenv(const char *name);
list_t *path_list();
void print_dirs_in_path(void);

/**
 * main - prints
 * Return: always 0
 */
int main(void)
{
	list_t *head = path_list();
	print_dirs_in_path();
	printf("\n*******************************************\n");
	print_list(head);

	return (0);
}

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

/**
 * add_node - adds a new node at the beginning of a list_t list
 * @head: pointer to head pointer to the list
 * @str: pointer to the string to add
 * Return: pointer to the new element
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *temp = NULL;

	if (!str)
		return (NULL);

	temp = malloc(sizeof(list_t));

	if (!temp)
		return (NULL);

	temp->str = strdup(str);

	if (!temp->str)
	{
		free(temp);
		return (NULL);
	}

	temp->len = (unsigned int)strlen(str);
	temp->next = NULL;

	if (!head)
	{
		*head = temp;
		return (temp);
	}
	temp->next = *head;
	*head = temp;

	return (temp);
}

int has_same_key(char *str, const char *substr);
char *get_value(char *str);
unsigned int key_len(char *str);

/**
 * _getenv - gets an environment variable
 * @name: pointer to name of variable
 * Return: pointer to environment variable
 */
char *_getenv(const char *name)
{
	char *value = NULL;
	unsigned int i = 0;

	while (environ[i] != NULL)
	{
		if (has_same_key(environ[i], name))
			value = get_value(environ[i]);
		i++;
	}
	return (value);
}

/**
 * key_len - calculated length of environment variable's key
 * @str: pointer to environment variable
 * Return: length of key
 */
unsigned int key_len(char *str)
{
	unsigned int len = 0;

	while (*str != '=')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * has_same_key - checks if two keys are the same
 * @str: pointer to environment variable
 * @substr: pointer to a key
 * Return: 1 if same, 0 otherwise
 */
int has_same_key(char *str, const char *substr)
{
	unsigned int key_length = 0;
	unsigned int substr_length = (unsigned int)strlen(substr);

	key_length = key_len(str);

	if (key_length != substr_length)
		return (0);

	while (*str != '=')
	{
		if (*str != *substr)
			return (0);
		str++;
		substr++;
	}
	return (1);
}

/**
 * get_value - get a pointer to start of an environment variable's value
 * @str: pointer to environment variable
 * Return: pointer to start of value
 */
char *get_value(char *str)
{
	while (*str != '=')
	{
		str++;
	}
	/* Point to next character after = */
	str++;

	return (str);
}
/**
 * print_list - prints all elements of a list
 * @h: pointer to a list
 * Return: number of nodes
 */
size_t print_list(const list_t *h)
{
	size_t length = 0;
	const list_t *temp = NULL;

	if (!h)
		return (length);
	temp = h;
	while (temp)
	{
		length++;
		if (temp->str)
			printf("[%u] %s\n", temp->len, temp->str);
		else
			printf("[0] (nil)\n");
		temp = temp->next;
	}
	return (length);
}

/**
 * print_dirs_in_path - prints each dir contained in the environment variable
 */
void print_dirs_in_path(void)
{
	char *value = _getenv("PATH");

	while (*value != '\0')
	{
		if (*value == ':')
		{
			putchar('\n');
		}
		else
		{
			putchar(*value);
		}
		value++;
	}
	putchar('\n');
}