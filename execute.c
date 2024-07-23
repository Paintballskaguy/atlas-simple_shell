#include "shell.h"

/**
 * execute - Executes a command
 * @argv: Array of arguments
 */
void execute(char **argv)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        /* Child process */
        if (execve(argv[0], argv, NULL) == -1)
        {
            perror(argv[0]);
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
