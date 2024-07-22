#include "shell.h"

void launch_prog(Command *cmd)
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
        /* Child process */
        execvp(cmd->args[0], cmd->args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        waitpid_wrapper(pid, &status, 0);
    }
}
