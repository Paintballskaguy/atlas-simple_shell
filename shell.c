#include "shell.h"

/**
 * init - Initialize the shell
 */
void init(void)
{
    /* Handle signals */
    signal(SIGINT, handle_signal);
}

/**
 * handle_signal - Handle signals
 * @sig: Signal number
 */
void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n"); /* Print a new line */
        shell_prompt(); /* Display the prompt again */
        fflush(stdout); /* Flush the output buffer */
    }
}

/**
 * shell_prompt - Display the shell prompt
 */
void shell_prompt(void)
{
    printf("#cisfun$ ");
    fflush(stdout);
}

/**
 * command_handler - Handles command execution
 * @cmd: Command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int command_handler(char *cmd)
{
    pid_t pid;
    int status;

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
        char *args[] = {cmd, NULL};
        execve(cmd, args, environ);
        /* If execve fails */
        perror(cmd);
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
 * main - Entry point for the shell
 *
 * Return: 0 on success, -1 on failure
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    init(); /* Initialize the shell */

    while (1)
    {
        shell_prompt(); /* Display the shell prompt */
        
        read = getline(&line, &len, stdin); /* Read input from the user */
        if (read == -1)
        {
            if (feof(stdin))
            {
                /* Handle end-of-file condition (Ctrl+D) */
                printf("\n");
                break;
            }
            else if (errno == EINTR)
            {
                /* Interrupted by signal */
                clearerr(stdin); /* Clear the error */
                continue;
            }
            else
            {
                perror("getline");
                break;
            }
        }

        /* Remove newline character from the input line */
        if (line[read - 1] == '\n')
        {
            line[read - 1] = '\0';
        }

        /* Handle empty command */
        if (line[0] == '\0')
        {
            continue;
        }

        /* Handle command */
        command_handler(line);
    }

    free(line); /* Free the line buffer */
    return 0;
}

