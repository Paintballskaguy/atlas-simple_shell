#include "shell.h"

/**
 * file_io - Handles input and output redirection for a command
 * @cmd: The command structure containing the command and its arguments
 * @option: Specifies the redirection type (0 for input, 1 for output)
 */
void file_io(Command *cmd, int option)
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
        if (option == 0)
        {
            /* Input redirection */
            int fd0 = open(cmd->inputFile, O_RDONLY); /* Open the input file for reading */
            if (fd0 == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd0, STDIN_FILENO); /* Redirect standard input to the file */
            close(fd0); /* Close the file descriptor */
        }
        else if (option == 1)
        {
            /* Output redirection */
            int fd1 = open(cmd->outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); /* Open the output file for writing, create if it doesn't exist, truncate if it does */
            if (fd1 == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd1, STDOUT_FILENO); /* Redirect standard output to the file */
            close(fd1); /* Close the file descriptor */
        }

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
