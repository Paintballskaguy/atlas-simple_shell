#include "shell.h"

/**
 * get_custom_env - Retrieve the value of a custom environment variable
 * @var: The name of the environment variable to retrieve
 *
 * Return: The value of the environment variable, or NULL if not found
 */
char *get_custom_env(char *var)
{
	extern char **environ; /* Access to environment variables */
	int i;

	/* Iterate through the environment variables */
	for (i = 0; environ[i] != NULL; i++)
	{
		/* Check if the current environment variable matches the given name */
		if (strncmp(environ[i], var, strlen(var)) == 0)
		{
			/* Return the value of the environment variable */
			return (environ[i] + strlen(var) + 1);
		}
	}
	/* Return NULL if the environment variable is not found */
	return (NULL);
}

/**
 * shell_prompt - Display the shell prompt
 */
void shell_prompt(void)
{
	char hostn[1204] = ""; /* Buffer to store the hostname */
	char *user = get_custom_env("LOGNAME"); /* Retrieve the username from the environment */

	/* Get the hostname and store it in the buffer */
	gethostname(hostn, sizeof(hostn));

	/* Print the shell prompt in the format: user@hostname currentDirectory > */
	printf("%s@%s %s > ", user, hostn, getcwd(currentDirectory, 1024));
}
