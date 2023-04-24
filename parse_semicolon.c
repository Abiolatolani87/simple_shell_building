#include "main.h"

/**
 * starts_with_semicolon - checks if string starts with ';'
 * @str: pointer to string to check
 * Return: 1 if true, 0 otherwise
*/
int starts_with_semicolon(char *str)
{
	int valid_char_found = 0;

	while (*str != '\0')
	{
		if (*str == ';' && !valid_char_found)
			return (1);
		if (*str != ' ' && *str != '\n')
			return (0);
		str++;
	}
	return (0);
}


/**
 * has_consecutive_semicolon - checks if string has consecutive ';'
 * @str: pointer to string to check
 * Return: 1 if true, 0 otherwise
*/
int has_consecutive_semicolon(char *str)
{
	int semicolon_exist = 0;

	while (*str != '\0')
	{
		if (*str == ';')
		{
			if (semicolon_exist)
				return (1);
			semicolon_exist = 1;
		}
		else
		{
			if (*str != ' ')
				semicolon_exist = 0;
		}
		str++;
	}
	return (0);
}

/**
 * parse_semicolon - tokenize string by ';'
 * @str: pointer to string to tokenize
 * Return: pointer to tokenized string
*/
char **parse_semicolon(char *str, int *status, list_t *head)
{
	char *strR = NULL;
	char **str_p = NULL;

	if (str == NULL)
		return (NULL);

	if (starts_with_semicolon(str) || has_consecutive_semicolon(str))
	{
		// _puts("bash: syntax error");
		// *status = 127;

		return (NULL);
	}

	str_p = str_into_tokens(str, ';', head);

	return (str_p);
}
