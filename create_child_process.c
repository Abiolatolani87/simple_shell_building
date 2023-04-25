#include "main.h"

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
		perror(argv[0]);
		*status = 127;
	}
	else
	{
		/*argv[0] = file_fullpath;*/
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(1);
		}
		if (child_pid == 0)
		{
			if (execve(file_fullpath, argv, environ) == -1)
			{
				perror(argv[0]);
				exit(1);
			}
		}
		else
		{
			if (wait(status) == -1)
			{
				perror("Error");
				exit(1);
			}
		}
	}
	
	free(file_fullpath);
	free_allocated_memory(head_path, dirs);
}
