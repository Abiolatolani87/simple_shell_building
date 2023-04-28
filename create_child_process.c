#include "main.h"

void handle_nonpath_error(char **argv, int *status);

/**
 * create_child_process - forks a parent process to run a command
 * @status: pointer to exit code
 * @argv: pointer to command
*/
void create_child_process(int *status, char **argv)
{
	char **dirs = NULL;
	list_t *head_path = NULL;
	char *file_fullpath = NULL;
	pid_t child_pid;

	interpret_dollar(argv, *status);
	file_fullpath = check_path(argv[0], dirs, head_path);
	if (file_fullpath == NULL)
	{
		handle_nonpath_error(argv, status);
	}
	else
	{
		/*argv[0] = file_fullpath;*/
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(2);
		}
		if (child_pid == 0)
		{
			if (execve(file_fullpath, argv, environ) == -1)
			{
				perror(argv[0]);
				exit(2);
			}
			*status = 0;
		}
		else
		{
			if (wait(status) == -1)
			{
				perror("Error");
				exit(2);
			}
		}
		_free(file_fullpath);
		file_fullpath = NULL;
	}
	/*free_allocated_memory(head_path, dirs);*/
}

/**
 * handle_nonpath_error - print error
 * @argv: pointer to command
 * @status: pointer to exit code
*/
void handle_nonpath_error(char **argv, int *status)
{
	if (!has_forward_slash(argv[0]))
	{
		custom_print(2, "%s: %d: %s: not found\n", argvalues[0],
			     count_args(argv), argv[0]);
	}
	else
		perror(argv[0]);
	*status = 127;
}
