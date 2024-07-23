#include "shell.h"

/* External declaration for environ */
extern char **environ;

/* Function prototypes */
void init(void);
void shell_prompt(void);
int command_handler(char *cmd);
void handle_signal(int sig);

/* Global variable to check if the shell is interactive */
int is_interactive;

/**
 * init - Initialize the shell
 */
void init(void)
{
    /* Handle signals */
    signal(SIGINT, handle_signal);

    /* Determine if the shell is interactive */
    is_interactive = isatty(STDIN_FILENO);
}

/**
 * handle_signal - Handle signals
 * @sig: Signal number
 */
void handle_signal(int sig)
{
    if (sig == SIGINT)
    {
        if (is_interactive)
        {
            printf("\n"); /* Print a new line */
            shell_prompt(); /* Display the prompt again */
            fflush(stdout); /* Flush the output buffer */
        }
    }
}

/**
 * shell_prompt - Display the shell prompt
 */
void shell_prompt(void)
{
    if (is_interactive)
    {
        printf("#cisfun$ ");
        fflush(stdout);
    }
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
    char *args[2]; /* Arguments array */
    int status;

    args[0] = cmd;
    args[1] = NULL;

    /* Handle the "exit" command to exit the shell */
    if (strcmp(cmd, "exit") == 0)
    {
        exit(0); /* Exit the shell */
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
        if (execve(cmd, args, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
        return 0;
    }
    return 0; /* Ensure function has a return value */
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
            if (errno == EINTR)
            {
                /* Interrupted by signal */
                clearerr(stdin); /* Clear the error */
                continue;
            }
            else
            {
                /* Handle end-of-file condition or other errors */
                printf("\n");
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

