#include "main.h"

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
	// static char *curr = "static!";
	// printf("%s\n", curr);

	// const char *s = "  /biin/ls -l /tmp  ";
	// int i = 0;
	// char **strs = str_into_tokens(s, ' ');
	// while (strs[i] != NULL)
	// {
	// 	printf("%s\n", strs[i]);
	// 	i++;
	// }
	int a = check_path("ls");
	printf("a: %d\n", a);

	return (0);
}