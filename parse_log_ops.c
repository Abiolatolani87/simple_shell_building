#include "main.h"

void search_for_ops(char curr_ch, char next_ch, int *found, char *op);
void add_token_op_to_list(char *token_buf, list_t *tokens_h,
			  list_t *ops_h, char *op, int *buf_index, int *started, int *found);
void add_token_to_list(char curr_ch, char *token_buf, list_t *tokens_h,
		       int *buf_index, int *started);

/**
 * parse_logical_ops_r - tokenize string by && and ||
 * @str: pointer to string to tokenize
 * Return: pointer to tokenized string
*/
cmd_ops *parse_logical_ops(char *str)
{
	int op_found = 0, token_started = 0, buffer_index = 0;
	int i = 0, tokens_list_len = 0, ops_list_len = 0;
	char op_str[3] = {0};
	char token_buffer[1024] = {0};
	list_t *tokens_head = NULL;
	list_t *ops_head = NULL;
	char **ptr_to_cmd_tokens = NULL;
	char **ptr_to_ops_tokens = NULL;
	cmd_ops *ptr_to_cmd_and_ops = NULL;

	while (str[i] != '\0')
	{
		search_for_ops(str[i], str[i + 1], &op_found, op_str);

		if ((op_found && !token_started) || (op_found && str[i + 2] == '\0'))
		{
			if (tokens_head)
				free_list(tokens_head);
			if (ops_head)
				free_list(ops_head);

			return (NULL);
		}
		else if (op_found && token_started && str[i + 2] != '\0')
		{
			add_token_op_to_list(token_buffer, tokens_head, ops_head,
					     op_str, &buffer_index, &token_started, &op_found);
			i += 2;
		}
		else if (token_started && !op_found && str[i + 1] == '\0')
		{
			add_token_to_list(str[i], token_buffer, tokens_head,
					  &buffer_index, &token_started);
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
	ptr_to_cmd_and_ops->cmd_tokens = store_str_ptrs(tokens_head,
							ptr_to_cmd_tokens);
	ptr_to_cmd_and_ops->ops_tokens = store_str_ptrs(ops_head, ptr_to_ops_tokens);

	return (ptr_to_cmd_and_ops);
}

/**
 * search_for_ops - finds and stores logical operator
 * @curr_ch: current character
 * @next_ch: next character
 * @found: op found flag
 * @op: array to old logical operator
*/
void search_for_ops(char curr_ch, char next_ch, int *found, char *op)
{
	if (curr_ch == '&' && next_ch == '&')
	{
		*found = 1;
		_strcpy(op, "&&");
	}
	else if (curr_ch == '|' && next_ch == '|')
	{
		*found = 1;
		_strcpy(op, "||");
	}
}

/**
 * add_token_and_op_to_list - add token and logical op to their respective list
 * @token_buf: token to add
 * @tokens_h: pointer to tokens list
 * @ops_h: pointer to logical ops list
 * @op: logical operator to add
 * @buf_index: current buffer index
 * @started: token started flag
 * @found: op found flag
*/
void add_token_op_to_list(char *token_buf, list_t *tokens_h, list_t *ops_h,
			  char *op, int *buf_index, int *started, int *found)
{
	token_buf[*buf_index] = '\0';
	tokens_h = add_node_end(tokens_h, token_buf);
	ops_h = add_node_end(ops_h, op);
	*started = 0;
	*found = 0;
	*buf_index = 0;
}

/**
 * add_token_to_list - add token and logical op to their respective list
 * @curr_ch: current character
 * @token_buf: token to add
 * @tokens_h: pointer to tokens list
 * @buf_index: current buffer index
 * @started: token started flag
*/
void add_token_to_list(char curr_ch, char *token_buf, list_t *tokens_h,
		       int *buf_index, int *started)
{
	token_buf[*buf_index] = curr_ch;
	(*buf_index)++;
	token_buf[*buf_index] = '\0';
	tokens_h = add_node_end(tokens_h, token_buf);
	*started = 0;
	*buf_index = 0;
}
