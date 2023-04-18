#include "main.h"

/**
 * main - super simple shell
 * Return: Always 0
 */
int main(void)
{
	pid_t child_pid;
	int status, i = 0;
	FILE *stream = stdin;
	char *line = NULL, *path_to_exec = NULL;
	size_t len = 0;
	ssize_t bytes_read = 0;
	char **dirs = NULL;
	list_t *head_path = NULL;
	list_t *head_arvg = NULL;
	char delim = ' ';
	char *file_fullpath = NULL;

	printf("#cisfun$ ");
	while ((bytes_read = getline(&line, &len, stream)) != -1)
	{
		dirs = NULL;
		head_path = NULL;
		head_arvg = NULL;
		file_fullpath = NULL;

		char **argv = str_into_tokens(line, delim, head_arvg);
		// printf("argv[0]: %s\n", argv[0]);
		/* check if file exist in PATH */
		file_fullpath = check_path(argv[0], dirs, head_path);
		// printf("After check path argv[0]: %s\n", argv[0]);
		// printf("file full path: %s\n", file_fullpath);

		if (file_fullpath == NULL)
		{
			perror(argv[0]);
			printf("#cisfun$ ");
		}
		else
		{
			/* change argv[0] to point to fullpath */
			argv[0] = file_fullpath;

			/**
			 * TEST:
			*/
			// printf("argv[0]: %s\n", argv[0]);
			// printf("file fullpath: %s\n", file_fullpath);

			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error");
				return (1);
			}
			if (child_pid == 0)
			{
				if (execve(argv[0], argv, environ) == -1)
				{
					perror(argv[0]);
					free_list(head_arvg);
					// free(file_fullpath);
					printf("#cisfun$ ");
				}
				
				// free(file_fullpath);
				// free(dirs);
			}
			else
			{
				if (wait(&status) == -1)
				{
					perror("Error");
					return (1);
				}
				//free(file_fullpath);
				free_list(head_arvg);
				printf("2nd prompt #cisfun$ ");
			}
		}
	}

	free(line);
	fclose(stream);

	return (0);
}