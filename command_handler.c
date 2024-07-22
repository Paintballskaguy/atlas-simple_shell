#include "shell.h"

/**
 * free_command - Frees the memory allocated for a Command structure
 * @cmd: The command structure to free
 */
void free_command(Command *cmd)
{
	int i = 0;

	if (cmd) /* Check if the command structure is not NULL */
	{
		/* Free each argument string in the command */
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}

		/* Free the input file string if it exists */
		free(cmd->inputFile);
		/* Free the output file string if it exists */
		free(cmd->outputFile);
		/* Free the command structure itself */
		free(cmd);
	}
}

/**
 * command_handler - Handles the execution of a command
 * @cmd: The command structure containing the command and its arguments
 *
 * Return: 0 on success, -1 on failure
 */
int command_handler(Command *cmd)
{
	pid_t pid; /* Process ID for fork */

	/* Check if the command structure or the first argument is NULL */
	if (cmd == NULL || cmd->args[0] == NULL)
	{
		return -1; /* No command to handle */
	}

	/* Check if the command is "exit" */
	if (strcmp(cmd->args[0], "exit") == 0)
	{
		exit(0); /* Exit the shell */
	}

	/* Check if the command is "cd" */
	if (strcmp(cmd->args[0], "cd") == 0)
	{
		change_directory(cmd->args); /* Change directory */
		return 0;
	}

	/* Fork a new process */
	pid = fork();
	if (pid == -1)
	{
		/* Fork failed */
		perror("fork");
		return -1;
	}
	else if (pid == 0)
	{
		/* Child process */
		execvp(cmd->args[0], cmd->args); /* Execute the command */
		perror("execvp");				 /* If execvp fails, print an error message */
		exit(EXIT_FAILURE);				 /* Exit with failure */
	}
	else
	{
		/* Parent process */
		int status;
		waitpid(pid, &status, 0); /* Wait for the child process to finish */
		return 0;
	}
}
