#include "shell.h"

/* Forward declaration for find_command */
char *find_command(char *command);

/**
 * command_handler - Handles command execution
 * @cmd: Command structure containing command and arguments
 *
 * Return: 0 on success, -1 on failure
 */
int command_handler(Command *cmd)
{
    pid_t pid; /* Process ID for fork */
    int status; /* Status of the child process */
    char *path; /* Path for the command if found */

    if (cmd == NULL || cmd->args[0] == NULL)
    {
        return -1;  /* No command to handle */
    }

    /* Handle built-in exit command */
    if (strcmp(cmd->args[0], "exit") == 0)
    {
        exit(0);  /* Exit the shell */
    }

    /* Handle built-in cd command */
    if (strcmp(cmd->args[0], "cd") == 0)
    {
        change_directory(cmd->args);
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
        if (strchr(cmd->args[0], '/') == NULL)
        {
            /* Use find_command if the command is not an absolute path */
            path = find_command(cmd->args[0]);
            if (path == NULL)
            {
                fprintf(stderr, "%s: command not found\n", cmd->args[0]);
                exit(EXIT_FAILURE);
            }
            execvp(path, cmd->args);
            free(path);
        }
        else
        {
            execvp(cmd->args[0], cmd->args);
        }
        /* If execvp fails */
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0); /* Wait for the child process to finish */
        return 0;
    }
}

/**
 * find_command - Searches for a command in the PATH environment variable
 * @command: The command to search for
 *
 * Return: The full path to the command if found, NULL otherwise
 */
char *find_command(char *command)
{
    char *path = getenv("PATH"); /* Get the PATH environment variable */
    char *path_copy; /* Copy of PATH to avoid modifying the original */
    char *dir; /* Directory in PATH */
    char *full_path = malloc(1024); /* Allocate memory for the full path */

    if (path == NULL || full_path == NULL)
    {
        if (full_path)
            free(full_path);
        return NULL;
    }

    path_copy = strdup(path); /* Make a copy of PATH */
    if (path_copy == NULL)
    {
        free(full_path);
        return NULL;
    }

    dir = strtok(path_copy, ":"); /* Tokenize the PATH variable */
    while (dir != NULL)
    {
        snprintf(full_path, 1024, "%s/%s", dir, command); /* Construct the full path */
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path; /* Command found */
        }
        dir = strtok(NULL, ":"); /* Continue to the next directory in PATH */
    }

    free(path_copy);
    free(full_path);
    return NULL; /* Command not found */
}

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
