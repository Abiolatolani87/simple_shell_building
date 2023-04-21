#include "main.h"

/**
 * main - super simple shell
 * Return: Always 0
 */
int main(void)
{
	pid_t child_pid;
	int status = 0, i = 0;
	FILE *stream = stdin;
	char *line = NULL, *path_to_exec = NULL;
	size_t len = 0;
	ssize_t bytes_read = 0;
	char **dirs = NULL;
	list_t *head_path = NULL;
	list_t *head_arvg = NULL;
	char delim = ' ';
	char *file_fullpath = NULL;
	char *builtin[] = {"exit", "setenv", "unsetenv", "cd", "getenv", NULL};




	while (1)
	{
		prompt_user();

		if ((bytes_read = getline(&line, &len, stream)) == -1)
		{
			_putchar('\n');
			exit(1);
		}
		char **argv = str_into_tokens(line, delim, head_arvg);

		if (built_in(argv[0], builtin))
		{
			execute_builtin_cmd(argv, &status);
		}
		else
		{
			interpret_dollar(argv, status);

			file_fullpath = check_path(argv[0], dirs, head_path);

			if (file_fullpath == NULL)
			{
				perror(argv[0]);
				status = 127;
			}
			else
			{
				/* change argv[0] to point to fullpath */
				argv[0] = file_fullpath;

				child_pid = fork();
				if (child_pid == -1)
				{
					perror("Error");
					exit(1);
				}
				if (child_pid == 0)
				{
					if (execve(argv[0], argv, environ) == -1)
					{
						perror(argv[0]);
						exit(1);
					}
				}
				else
				{
					if (wait(&status) == -1)
					{
						perror("Error");
						exit(1);
					}
					//free(file_fullpath);
					free_list(head_arvg);
				}
			}
		}
	}

	free(line);
	fclose(stream);

	return (0);
}

void prompt_user(void)
{
	char buffer[1024] = {0};
	printf("%s ", getcwd(buffer, 1024));
	printf("#cisfun$ ");
}

void execute_builtin_cmd(char **argv, int *status)
{
	int argv_count = 0;

	argv_count = count_strs(argv);
	if (_strcmp(argv[0], "exit") == 0)
	{
		handle_exit(argv_count, argv);
	}
	else if (_strcmp(argv[0], "setenv") == 0)
	{
		handle_setenv(argv_count, argv, &status);
	}
	else if (_strcmp(argv[0], "unsetenv") == 0)
	{
		handle_unsetenv(argv_count, argv, &status);
	}
	else if (_strcmp(argv[0], "cd") == 0)
	{
		handle_cd(argv_count, argv, &status);
	}
	else if (_strcmp(argv[0], "getenv") == 0)
	{
		printf("%s: %s\n", argv[1], _getenv(argv[1]));
	}
}

void handle_exit(int argv_count, char **argv)
{
	int exit_code = 0;

	if (argv_count > 2)
	{
		newputs("exit");
		newputs("bash: exit: ");
		newputs(argv[1]);
		_puts(": wrong argument count");
		exit(2);
	}
	else if (argv_count == 1)
	{
		_puts("exit");
		exit(0);
	}
	else
	{
		if (is_all_digits(argv[1]))
		{
			exit_code = _atoi(argv[1]);
			exit(exit_code);
		}
		else
		{
			_puts("exit");
			newputs("bash: exit: ");
			newputs(argv[1]);
			newputs(": numeric argument required");
			exit(2);
		}
	}
}

void handle_setenv(int argv_count, char **argv, int *status)
{
	if (argv_count != 3)
	{
		fprintf(stderr, "%s:usage: %s VARIABLE VALUE\n", argv[0], argv[0]);
		*status = 127;
	}
	else
	{
		if ((_setenv(argv[1], argv[2], 1)) == -1)
		{
			_puts("command invoked cannot execute");
			*status = 126;
		}
	}
}

void handle_unsetenv(int argv_count, char **argv, int *status)
{
	if (argv_count != 2)
	{
		fprintf(stderr, "%s:usage: %s VARIABLE\n", argv[0], argv[0]);
		*status = 127;
	}
	else
	{
		if ((_unsetenv(argv[1])) == -1)
		{
			_puts("command invoked cannot execute");
			*status = 126;
		}
	}
}

void handle_cd(int argv_count, char **argv, int *status)
{
	char *env_value = NULL, *curr_dir = NULL, *home_value = NULL;

	curr_dir = _strdup(_getenv("PWD"));
	env_value = _strdup(_getenv("OLDPWD"));

	if (argv_count > 2)
	{
		fprintf(stderr, "%s:usage: %s [DIRECTORY]\n", argv[0], argv[0]);
		*status = 127;
	}
	else if (argv_count == 2)
	{
		if (_strcmp(argv[1], "-") == 0)
		{
			if (chdir(env_value) == -1)
			{
				perror(argv[0]);
				perror(argv[1]);
			}
			else
			{
				_setenv("OLDPWD", curr_dir, 1);
				_setenv("PWD", env_value, 1);
			}
		}
		else
		{
			if (chdir(argv[1]) == -1)
			{
				perror(argv[0]);
				perror(argv[1]);
			}
			else
			{
				_setenv("OLDPWD", curr_dir, 1);
				/* TODO: call getcwd(buffer, size)then set PWD with string in buffer */
				_setenv("PWD", argv[1], 1);
			}
		}
	}
	else
	{
		home_value = _strdup(_getenv("HOME"));
		if (chdir(home_value) == -1)
		{
			perror(argv[0]);
			perror(argv[1]);
		}
		else
		{
			_setenv("OLDPWD", curr_dir, 1);
			_setenv("PWD", home_value, 1);
		}
	}
	free(curr_dir);
	free(env_value);
	free(home_value);
}