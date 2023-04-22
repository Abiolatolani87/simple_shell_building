#include "main.h"

void handle_cd(int argv_count, char **argv, int *status)
{
	char *env_value = NULL, *curr_dir = NULL, *home_value = NULL;

	curr_dir = _strdup(_getenv("PWD"));
	env_value = _strdup(_getenv("OLDPWD"));

	if (argv_count > 2)
	{
		//fprintf(stderr, "%s:usage: %s [DIRECTORY]\n", argv[0], argv[0]);
		newputs(argv[0]);
		newputs(":usage: ");
		newputs(argv[0]);
		_puts(" [DIRECTORY]");
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