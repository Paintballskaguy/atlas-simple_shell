#include "shell.h"

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
	char *argv[2];

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
		line = trim_whitespace(line);

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		argv[0] = line;
		argv[1] = NULL;

		execute(argv);
	}

	return (0);
}
