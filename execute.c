#include "shell.h"

extern char **environ;

/**
 * get_path - Retrieves the PATH environment variable
 *
 * Return: A pointer to the value of the PATH variable
 */
char *get_path(void)
{
	char **env = environ;
	char *path_prefix = "PATH=";
	size_t len = strlen(path_prefix);

	while (*env)
	{
		if (strncmp(*env, path_prefix, len) == 0)
		{
			return *env + len;
		}
		env++;
	}
	return NULL;
}

/**
 * execute - Executes a command
 * @argv: Array of arguments
 *
 * Return: Exit status of the command
 */

int execute(char **argv)
{
	char *path, *cmd = NULL;
	char *path_env = get_path();
	char *path_dup = NULL;
	char *dir = NULL;
	pid_t pid;
	int status;

	if (path_env)
	{
		path_dup = strdup(path_env);
		dir = strtok(path_dup, ":");
	}

	if (access(argv[0], X_OK) == 0 || argv[0][0] == '.' || argv[0][0] == '/')
	{
		cmd = argv[0];
	}
	else if (path_env)
	{
		while (dir != NULL)
		{
			path = malloc(strlen(dir) + strlen(argv[0]) + 2);
			sprintf(path, "%s/%s", dir, argv[0]);

			if (access(path, X_OK) == 0)
			{
				cmd = path;
				break;
			}
			free(path);
			dir = strtok(NULL, ":");
		}

		if (dir == NULL)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]);
			free(path_dup);
			return; /* Command not found */
		}
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", argv[0]);
		return; /* Command not found */
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path_dup);
		return;
	}
	if (pid == 0)
	{
		/* Child process */
		if (execve(cmd, argv, environ) == -1)
		{
			perror(argv[0]);
			exit(1);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* Parent process */
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(path_dup);
	if (cmd != argv[0])
		free(cmd);

	return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
