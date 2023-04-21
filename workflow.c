void run_shell_v1()
{
	while (1)
	{
		prompt_user();
		readline();
		parse_semicolon();
		while (there_is_semicolon_sep_token())
		{
			parse_logical_operators();
			while (there_is_logical_ops_sep_token())
			{
				parse_cmd();
				if (first_token_isbuiltin())
					exec_builtin();
				else
				{
					int child_pid = fork_parent_process();
					if (child_pid == 0)
					{
						exec_cmd();
					}
					else
					{
						wait_for_child_process();
						free_allocated_memories_for_cmd();
					}
				}
				if (logical_op_is_not_null())
				{
					if (logical_op_and())
					{
						if (!prev_cmd_exited_successfully())
							break;
					}
					else if (logical_op_or())
					{
						if (prev_cmd_exited_successfully())
							break;
					}
				}
			}
			free_resources();
		}
	}
}
void run_shell_v2()
{
	while (1)
	{
		prompt_user();
		readline();
		parse_semicolon();
		while (there_is_semicolon_sep_token())
		{
			parse_logical_operators();
			while (there_is_logical_ops_sep_token())
			{
				parse_cmd();
				if (first_token_isbuiltin())
					exec_builtin();
				else
					fork_parent_and_exec_cmd();
				if (logical_op_is_not_null())
				{
					if (logical_op_and())
					{
						if (!prev_cmd_exited_successfully())
							break;
					}
					else if (logical_op_or())
					{
						if (prev_cmd_exited_successfully())
							break;
					}
				}
			}
			free_resources();
		}
	}
}

void current_flow()
{
	while (1)
	{
		prompt_user();
		readline();

		parse_cmd();
		if (first_token_isbuiltin())
			exec_builtin();
		else
			fork_parent_and_exec_cmd();

		free_resources();
	}
}
