#include "shell.h"

/**
 * execute - Executes a command
 * @argv: Array of arguments
 */
void execute(char **argv)
{
	char *path, *cmd;
	char *path_env = getenv("PATH");
	char *path_dup = strdup(path_env);
	char *dir = strtok(path_dup, ":");
	pid_t pid;
	int status;

	if (access(argv[0], X_OK) == 0)
	{
		cmd = argv[0];
	}
	else
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
			return;
		}
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
		if (execve(cmd, argv, NULL) == -1)
		{
			perror(argv[0]);
		}
		exit(EXIT_FAILURE);
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
}
