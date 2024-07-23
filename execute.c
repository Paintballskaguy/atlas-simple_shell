#include "shell.h"

/* Execute the given command */
void execute_command(char **args)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork failed");
        return;
    }
    else if (child_pid == 0)
    {
        /* Child process */
        if (execve(args[0], args, environ) == -1)
        {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        do
        {
            waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

