#include "shell.h"

extern char **environ;

/**
 * main - Entry point of the shell
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **argv;
	char *trimmed_line;
	int status = 0;

	while (1)
	{
		prompt();

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			/* Handle EOF (Ctrl+D) */
			if (line)
				free(line);
			break;
		}

		/* Remove newline character from the input */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Trim leading and trailing spaces */
		trimmed_line = trim_whitespace(line);

		/* Skip empty input */
		if (trimmed_line[0] == '\0')
		{
			free(line);
			line = NULL;
			continue;
		}

		if (strcmp(trimmed_line, "exit") == 0)
		{
			free(line);
			break;
		}

		/* Split the line into arguments */
		argv = split_line(trimmed_line);

		status = execute(argv);

		free(argv);
		free(line);
		line = NULL; /* Reset line to NULL to prevent double free */
	}

	return (status);
}
