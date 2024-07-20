#include "shell.h"
#include <unistd.h> /* Include this for fork, setenv, getcwd, and other POSIX functions */
#include <stdlib.h> /* Include this for setenv */
#include <stdio.h> /* Include this for printf */
#include <signal.h> /* Include this for kill */

/**
 * launch_prog - Launch a program
 * @cmd: Command to execute
 */

void launch_prog(Command *cmd)
{
	int err = -1;
	int fd;

	if ((pid = fork()) == -1)
	{
		printf("Child process could not be created\n");
		return;
	}

	if (pid == 0)
	{
		signal(SIGINT, SIG_IGN);
		setenv("parent", getcwd(currentDirectory, 1024), 1);

		if (cmd->inputFile)
		{
			fd = open(cmd->inputFile, O_RDONLY);
			if (fd == -1)
			{
				perror("open input file");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}

		if (cmd->outputFile)
		{
			fd = open(cmd->outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror("open output file");
				exit(EXIT_FAILURE);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}

		if (execvp(cmd->args[0], cmd->args) == err)
		{
			printf("Command not found\n");
			kill(getpid(), SIGTERM);
		}
	}

	if (cmd->background == 0)
	{
		waitpid_wrapper(pid, NULL, 0);
	}
	else
	{
		printf("Process created with PID: %ld\n", (long)pid);
	}
}
