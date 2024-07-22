#include "shell.h"

/**
 * free_command - Frees the memory allocated for a Command structure
 * @cmd: The command structure to free
 */
void free_command(Command *cmd)
{
    int i = 0;

    if (cmd)
    {
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }

        free(cmd->inputFile);
        free(cmd->outputFile);
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
    pid_t pid;

    if (cmd == NULL || cmd->args[0] == NULL)
    {
        return -1;  /* No command to handle */
    }

    if (strcmp(cmd->args[0], "exit") == 0)
    {
        exit(0);  /* Exit the shell */
    }

    if (strcmp(cmd->args[0], "cd") == 0)
    {
        change_directory(cmd->args);
        return 0;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return -1;
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
        int status;
        waitpid(pid, &status, 0);
        return 0;
    }
}
