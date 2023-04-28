#include "main.h"

/**
 * handle_cd - execute cd command
 * @argv_count: number of arguments
 * @argv: pointer to strings
 * @status: pointer to exit code
*/
void handle_cd(int argv_count, char **argv, int *status)
{
	char *env_value = NULL, *curr_dir = NULL, *home_value = NULL;

	curr_dir = _strdup(_getenv("PWD"));
	env_value = _strdup(_getenv("OLDPWD"));

	if (argv_count > 2)
		handle_usage_error(argv[0], status);
	else if (argv_count == 2)
	{
		if (_strcmp(argv[1], "-") == 0)
		{
			if (chdir(env_value) == -1)
				handle_error(argv[0], argv[1], status);
			else
				set_old_new_pwd(curr_dir, env_value, status);
		}
		else
		{
			if (chdir(argv[1]) == -1)
				handle_error(argv[0], argv[1], status);
			else
			{
				/* TODO: call getcwd(buffer, size)then set PWD with string in buffer */
				set_old_new_pwd(curr_dir, argv[1], status);
			}
		}
	}
	else
	{
		home_value = _strdup(_getenv("HOME"));
		if (chdir(home_value) == -1)
			handle_error(argv[0], argv[1], status);
		else
			set_old_new_pwd(curr_dir, home_value, status);
	}
	free(curr_dir);
	free(env_value);
	free(home_value);
}

/**
 * handle_error - print error and set exit code
 * @str_1: pointer to string
 * @str_2: pointer to string
 * @status: pointer to exit code
*/
void handle_error(char *str_1, char *str_2, int *status)
{
	/*perror(str_1);*/
	/*perror(str_2);*/
	*status = 0;
}

/**
 * set_old_new_pwd - set OLDPWD and PWD in env variable
 * @old_dir: pointer to string
 * @new_dir: pointer to string
 * @status: pointer to exit code
*/
void set_old_new_pwd(char *old_dir, char *new_dir, int *status)
{
	setenv("OLDPWD", old_dir, 1);
	setenv("PWD", new_dir, 1);
	*status = 0;
}

/**
 * handle_usage_error - handle error
 * @str: pointer to string
 * @status: pointer to exit code
*/
void handle_usage_error(char *str, int *status)
{
	/*custom_print(2, "%s:usage: %s [DIRECTORY]", str, str);*/
	*status = 0;
}
