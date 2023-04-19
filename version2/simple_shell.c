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
	list_t *head = NULL;
	char delim = ' ';

	printf("#cisfun$ ");
	while ((bytes_read = getline(&line, &len, stream)) != -1)
	{
		/**
		 * TODO:-
		 * Pass line read into custome tokenize function to break it down into tokens
		 * 	Above line will return argv
		 * pass first argv to check path function to check if path exist
		 * 	if path does not exist
		 * 		free the list
		 * 		free argv
		 * 		perror(argv[0]);
				printf("#cisfun$ ");
			else
				replace argv[0] with the return of check_path

		*/

		char **argv = str_into_tokens(line, delim, head);

		/* remove newline */
		//     path_to_exec = malloc(sizeof(char) * strlen(line));
		// i = 0;
		// while (line[i] != '\n')
		// {
		// 	path_to_exec[i] = line[i];
		// 	i++;
		// }
		// path_to_exec[i] = '\0';

		// char *argv[] = {path_to_exec, NULL};

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
				printf("#cisfun$ ");
			}
		}
		else
		{
			if (wait(&status) == -1)
			{
				perror("Error");
				return (1);
			}
			printf("#cisfun$ ");
		}
	}
	free(line);
	fclose(stream);

	return (0);
}