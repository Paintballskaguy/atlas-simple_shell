#include "shell.h"

/**
 * get_custom_env - Retrieve the value of a custom environment variable
 * @var: The name of the environment variable to retrieve
 *
 * Return: The value of the environment variable, or NULL if not found
 */
char *get_custom_env(char *var)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], var, strlen(var)) == 0)
		{
			return (environ[i] + strlen(var) + 1);
		}
	}
	return (NULL);
}

/**
 * shell_prompt - Display the shell prompt
 */
void shell_prompt(void)
{
	char hostn[1204] = "";
	char *user = get_custom_env("LOGNAME");

	gethostname(hostn, sizeof(hostn));
	printf("%s@%s %s > ", user, hostn, getcwd(currentDirectory, 1024));
}
