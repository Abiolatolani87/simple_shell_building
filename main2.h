#ifndef MAIN2_H
#define MAIN2_H

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

/**
 * struct tokenize_cmd_ops - commands and logical ops tokens
 * @cmd_tokens: commands tokens
 * @ops_tokens: logical ops tokens
 */
typedef struct tokenize_cmd_ops
{
	char **cmd_tokens;
	char **ops_tokens;
} cmd_ops;

#endif
