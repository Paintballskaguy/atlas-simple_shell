#include "shell.h"

/**
 * launch_prog - Launches a program by forking a child process
 * @cmd: The command structure containing the command and its arguments
 *
 * This function creates a new process to execute a given command. The parent
 * process waits for the child process to finish execution.
 */
void launch_prog(Command *cmd)
{
    pid_t pid; /* Process ID for fork */
    int status; /* Status of the child process */

    /* Fork a new process */
    if ((pid = fork()) == -1)
    {
        /* Fork failed */
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /* Child process */
        execvp(cmd->args[0], cmd->args); /* Execute the command */
        perror("execvp"); /* If execvp fails, print an error message */
        exit(EXIT_FAILURE); /* Exit with failure */
    }
    else
    {
        /* Parent process */
        waitpid_wrapper(pid, &status, 0); /* Wait for the child process to finish */
    }
}
