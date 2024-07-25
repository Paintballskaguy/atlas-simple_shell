#include "shell.h"

extern char **environ; /* Declare external environment variable */

/**
 * get_path - Retrieves the PATH environment variable
 *
 * Return: A pointer to the value of the PATH variable
 */
char *get_path(void)
{
	char **env = environ;			  /* Initialize env to point to the environment variables */
	char *path_prefix = "PATH=";	  /* Define the prefix to search for */
	size_t len = strlen(path_prefix); /* Get the length of the prefix */

	while (*env) /* Loop through the environment variables */
	{
		if (strncmp(*env, path_prefix, len) == 0) /* Check if the current variable starts with "PATH=" */
		{
			return *env + len; /* Return the value after "PATH=" */
		}
		env++; /* Move to the next environment variable */
	}
	return NULL; /* Return NULL if PATH is not found */
}

/**
 * execute - Executes a command
 * @argv: Array of arguments
 *
 * Return: Status of the executed command
 */
int execute(char **argv)
{
	char *path, *cmd = NULL;
	char *path_env = get_path(); /* Get the PATH environment variable */
	char *path_dup = NULL;
	char *dir = NULL;
	pid_t pid;
	int status;

	if (path_env)
	{
		path_dup = strdup(path_env); /* Duplicate the PATH string */
		dir = strtok(path_dup, ":"); /* Tokenize the PATH string using ":" as a delimiter */
	}

	if (access(argv[0], X_OK) == 0 || argv[0][0] == '.' || argv[0][0] == '/')
	{
		cmd = argv[0]; /* If the command is a valid path, use it */
	}
	else if (path_env)
	{
		while (dir != NULL) /* Loop through each directory in PATH */
		{
			path = malloc(strlen(dir) + strlen(argv[0]) + 2); /* Allocate memory for the full path */
			sprintf(path, "%s/%s", dir, argv[0]);			  /* Construct the full path */

			if (access(path, X_OK) == 0) /* Check if the constructed path is executable */
			{
				cmd = path; /* If executable, use it as the command */
				break;
			}
			free(path);				 /* Free the allocated memory for path */
			dir = strtok(NULL, ":"); /* Get the next directory */
		}

		if (dir == NULL)
		{
			fprintf(stderr, "%s: command not found\n", argv[0]); /* Print error if command not found */
			free(path_dup);										 /* Free the duplicated PATH string */
			return 127;											 /* Return error status */
		}
	}
	else
	{
		fprintf(stderr, "%s: command not found\n", argv[0]); /* Print error if PATH is not set */
		return 127;											 /* Return error status */
	}

	pid = fork();  /* Create a new process */
	if (pid == -1) /* Check if fork failed */
	{
		perror("fork"); /* Print error message */
		free(path_dup); /* Free the duplicated PATH string */
		return 1;		/* Return error status */
	}
	if (pid == 0) /* Child process */
	{
		if (execve(cmd, argv, environ) == -1) /* Execute the command */
		{
			perror(argv[0]); /* Print error message if execve fails */
		}
		exit(EXIT_FAILURE); /* Exit child process with failure status */
	}
	else /* Parent process */
	{
		do
		{
			waitpid(pid, &status, WUNTRACED); /* Wait for the child process to finish */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status)); /* Continue waiting if the process is not finished */
	}

	free(path_dup);		/* Free the duplicated PATH string */
	if (cmd != argv[0]) /* If cmd is not the original command */
		free(cmd);		/* Free the allocated memory for cmd */

	return status; /* Return the status of the executed command */
}
