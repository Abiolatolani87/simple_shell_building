#include "main.h"

/**
 * parse_logical_ops - tokenize string by && and ||
 * @str: pointer to string to tokenize
 * @status: exit code
 * Return: pointer to tokenized string
*/
cmd_ops *parse_logical_ops(char *str, int *status)
{
	int op_found = 0;
	int token_started = 0;
	int i = 0, tokens_list_len = 0, ops_list_len = 0;
	char *op_str = NULL;
	char token_buffer[1024] = {0};
	int buffer_index = 0;
	list_t *tokens_head = NULL;
	list_t *ops_head = NULL;
	char **ptr_to_cmd_tokens = NULL;
	char **ptr_to_ops_tokens = NULL;
	cmd_ops *ptr_to_cmd_and_ops = NULL;

	while (str[i] != '\0')
	{
		if (str[i] == '&' && str[i + 1] == '&')
		{
			op_found = 1;
			op_str = "&&";
		}
		else if (str[i] == '|' && str[i + 1] == '|')
		{
			op_found = 1;
			op_str = "||";
		}

		if ((op_found && !token_started) || (op_found && str[i + 2] == '\0'))
		{
			if (tokens_head)
				free_list(tokens_head);
			if (ops_head)
				free_list(ops_head);

			// _puts("bash: syntax error");
			// *status = 127;

			return (NULL);
		}
		else if (op_found && token_started && str[i + 2] != '\0')
		{
			token_buffer[buffer_index] = '\0';
			add_node_end(&tokens_head, token_buffer);
			add_node_end(&ops_head, op_str);
			token_started = 0;
			op_found = 0;
			i += 2;
			buffer_index = 0;
		}
		else if (token_started && !op_found && str[i + 1] == '\0')
		{
			token_buffer[buffer_index] = str[i];
			buffer_index++;
			token_buffer[buffer_index] = '\0';
			add_node_end(&tokens_head, token_buffer);
			token_started = 0;
			buffer_index = 0;
			i++;
		}
		else if (token_started && !op_found && str[i + 1] != '\0')
		{
			token_buffer[buffer_index] = str[i];
			buffer_index++;
			i++;
		}

		else
		{
			token_started = 1;
			token_buffer[buffer_index] = str[i];
			buffer_index++;
			i++;
		}
	}

	ptr_to_cmd_and_ops = malloc(sizeof(cmd_ops));

	tokens_list_len = list_len(tokens_head);
	ops_list_len = list_len(ops_head);

	ptr_to_cmd_tokens = malloc(sizeof(char *) * (tokens_list_len + 1));
	ptr_to_ops_tokens = malloc(sizeof(char *) * (ops_list_len + 1));
	ptr_to_cmd_and_ops->cmd_tokens = store_str_ptrs(tokens_head, ptr_to_cmd_tokens);
	ptr_to_cmd_and_ops->ops_tokens = store_str_ptrs(ops_head, ptr_to_ops_tokens);

	return (ptr_to_cmd_and_ops);
}
