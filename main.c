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
	// list_t *head = path_list();
	// print_dirs_in_path();
	// printf("\n*******************************************\n");
	// print_list(head);
	// printf("Before setenv call: %p\n", *environ);
	// setenv("FRESH", "tyvoiax", 1);
	// setenv("EMMA", "so cool", 1);
	// printf("After setenv call: %p\n", *environ);
	// printf("%s\n", unsetenv("FRESH"));
	// printf("After setenv call: %p\n", *environ);
	// while (*environ)
	// 	printf("%s\n", *environ++);
	// *environ++ = "HEY=just trying";
	// *environ == NULL;

	// printf("After setenv call: %p\n", *environ);
	// printf("After setenv call: %s\n", *--environ);
	static char *curr = "static!";
	printf("%s\n", curr);
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

/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to head pointer to the list
 * @str: pointer to the string to add
 * Return: pointer to the new element
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *temp = NULL;
	list_t *curr_node = NULL;

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

	if (!*head)
	{
		*head = temp;
		return (temp);
	}
	curr_node = *head;

	while (curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = temp;

	return (temp);
}

/**
 * list_len - returns the number of elements in a linked list_t list
 * @h: pointer to the list
 * Return: number of elements in the list
 */
size_t list_len(const list_t *h)
{
	size_t length = 0;
	const list_t *temp = NULL;

	if (!h)
		return (length);
	temp = h;
	while (temp)
	{
		if (temp->str)
			length++;
		temp = temp->next;
	}
	return (length);
}

/**
 * store_str_ptrs - store the addresses of all strings in the list
 * @h: pointer to a list
 * Return: array of pointers to string
 */
char **store_str_ptrs(const list_t *h, char **ptrs_to_str)
{
	const list_t *temp = NULL;
	int i = 0;

	if (!h)
		return (NULL);

	while (h)
	{
		if (h->str)
		{
			ptrs_to_str[i] = h->str;
			i++;
		}

		h = h->next;
	}
	ptrs_to_str[i] = NULL;

	return (ptrs_to_str);
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

int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0;
	int environ_count = 0;
	char *new_env_str = NULL;
	char **new_environ = NULL;
	/* calculate length of env variable. Two for '=' and '\0'*/
	int new_env_var_len = strlen(name) + strlen(value) + 2;

	if (!name || !value)
		return (-1);
	new_env_str = malloc(new_env_var_len);

	if (!new_env_str)
		return (-1);
	snprintf(new_env_str, new_env_var_len, "%s=%s", name, value);
	/* Loop through environ and check if an environment variable starts with name*/
	while (environ[i])
	{
		if (strncmp(environ[i], name, strlen(name)) == 0)
		{
			if (!overwrite)
				return (0);
			else
			{
				strncpy(environ[i], new_env_str, new_env_var_len);
				return (0);
			}
		}
		i++;
	}
	/* Below line only executes if environment variable does not exist */
	new_environ = realloc(environ, sizeof(char *) * environ_count);
	if (!new_environ)
		return (-1);
	environ = new_environ;
	environ[environ_count] = new_env_str;
	environ[environ_count + 1] = NULL;
	return (0);
}

int _unsetenv(const char *name)
{
	int found = 0, i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], name, strlen(name)) == 0)
		{
			free(environ[i]);
			found = 1;
			break;
		}
		i++;
	}
	if (found)
	{
		/* Move remaining environment variables back by 1 */
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
		return (0);
	}
	else
		return (-1);
}

/* split strings into tokens */
/**
 * create a list
 * extact each token
 * create a node with the token
 * add node to end of list
 * create array of pointers to each token in the list
 * Add null to the array created
 * return the array of pointers (that will be argv for our shell )
*/
char **str_into_tokens(const char *str, char delim)
{
	char buffer[1024] = {0};
	int i = 0;
	list_t *head = NULL;

	if (!str)
		return (NULL);
	/* Extract tokens */
	while (*str != '\0')
	{
		/* look for first character that is not delimeter */
		while (*str == delim)
			str++;
		
		/* write characters upto next delimeter*/
		while (*str != delim || *str != '\0' || *str != '\n')
		{
			buffer[i] = *str;
			str++;
			i++;
		}
		buffer[i] = '\0';

		/* add token to end of list */
		add_node_end(&head, buffer);

		/* reset i for buffer reuse */
		i = 0;
		/* go to next character and repeat */
		str++;
	}
	/**
	 * TODO: 
	 * count nodes in list
	 * create an array of pointers to strings of size list
	 * store address of string in each node in the created array
	 * add NULL to the end
	 * return array */

	int list_length = list_len(head);
	/* plus 1 to accomate the NULL */
	char **ptr_to_tokens = malloc(sizeof(char *) * (list_length + 1));

	store_str_ptrs(head, ptr_to_tokens);

	return (ptr_to_tokens);

	/**
	 * AFTERUSE:
	 * free memory allocated for list (call free list func)
	 * free memory allocated for array of pointers
	*/
}