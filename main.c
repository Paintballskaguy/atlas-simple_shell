#include "shell.h"

extern char **environ; /* Declare external environment variable */

/**
 * print_env - Prints the current environment variables
 */
void print_env(void)
{
	char **env = environ; /* Initialize env to point to the environment variables */

	while (*env) /* Loop through the environment variables */
	{
		printf("%s\n", *env); /* Print each environment variable */
		env++;				  /* Move to the next environment variable */
	}
}

/**
 * main - Entry point of the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;						/* Pointer to hold the input line */
	size_t len = 0;							/* Variable to hold the length of the input line */
	ssize_t read;							/* Variable to hold the number of characters read */
	char **argv;							/* Array to hold the command and its arguments */
	char *trimmed_line;						/* Pointer to hold the trimmed input line */
	int status = 0;							/* Variable to hold the status of the last executed command */
	int interactive = isatty(STDIN_FILENO); /* Check if the shell is interactive */

	if (interactive) /* Display the welcome screen if interactive */
	{
		welcome_screen();
		open_new_terminal();
	}

	while (1) /* Infinite loop to keep the shell running */
	{
		if (interactive)
		{
			prompt(); /* Display the shell prompt */
		}

		read = getline(&line, &len, stdin); /* Read input from the user */
		if (read == -1)						/* Check if end of file (Ctrl+D) is reached */
		{
			/* Handle EOF (Ctrl+D) */
			free(line); /* Free the memory allocated for the input line */
			break;		/* Exit the loop */
		}

		/* Remove newline character from the input */
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		/* Trim leading and trailing spaces */
		trimmed_line = trim_whitespace(line);

		/* Skip empty input */
		if (trimmed_line[0] == '\0')
		{
			free(line);	 /* Free the memory allocated for the input line */
			line = NULL; /* Reset the line pointer to NULL */
			continue;	 /* Continue to the next iteration of the loop */
		}

		if (strcmp(trimmed_line, "exit") == 0) /* Check if the user typed "exit" */
		{
			free(line); /* Free the memory allocated for the input line */
			break;		/* Exit the loop */
		}

		if (strcmp(trimmed_line, "env") == 0) /* Check if the user typed "env" */
		{
			print_env(); /* Print the environment variables */
			free(line);	 /* Free the memory allocated for the input line */
			line = NULL; /* Reset the line pointer to NULL */
			continue;	 /* Continue to the next iteration of the loop */
		}

		/* Split the line into arguments */
		argv = split_line(trimmed_line);

		status = execute(argv); /* Execute the command */

		free(argv);	 /* Free the memory allocated for the arguments */
		free(line);	 /* Free the memory allocated for the input line */
		line = NULL; /* Reset the line pointer to NULL to prevent double free */
	}

	if (interactive)
	{
		close_terminal();
	}

	return status; /* Return the status of the last executed command */
}
