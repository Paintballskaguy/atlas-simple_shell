#include "shell.h"
#include <unistd.h> /* Include this for fork, setenv, and other POSIX functions */
#include <stdlib.h> /* Include this for setenv and other standard library functions */

/**
 * file_io - Handle file input/output redirection
 * @cmd: Command to execute
 * @option: Option for file redirection (0: output, 1: input/output)
 */
void file_io(Command *cmd, int option)
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
		if (option == 0 && cmd->outputFile)
		{
			fd = open(cmd->outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (option == 1)
		{
			if (cmd->inputFile)
			{
				fd = open(cmd->inputFile, O_RDONLY, 0600);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}

			if (cmd->outputFile)
			{
				fd = open(cmd->outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}

		setenv("parent", getcwd(currentDirectory, 1024), 1);

		if (execvp(cmd->args[0], cmd->args) == err)
		{
			printf("err");
			kill(getpid(), SIGTERM);
		}
	}
	waitpid_wrapper(pid, NULL, 0);
}
