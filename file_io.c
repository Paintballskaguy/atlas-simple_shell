#include "shell.h"

void file_io(Command *cmd, int option)
{
    pid_t pid;
    int status;

    if ((pid = fork()) == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        if (option == 0)
        {
            int fd0 = open(cmd->inputFile, O_RDONLY);
            if (fd0 == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd0, STDIN_FILENO);
            close(fd0);
        }
        else if (option == 1)
        {
            int fd1 = open(cmd->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd1 == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd1, STDOUT_FILENO);
            close(fd1);
        }

        execvp(cmd->args[0], cmd->args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid_wrapper(pid, &status, 0);
    }
}

