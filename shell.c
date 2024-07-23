#include "shell.h"

/* External declaration for environ */
extern char **environ;

/* Function prototypes */
void init(void);
void shell_prompt(void);
int command_handler(char *cmd);
char *find_command(char *command);
void handle_signal(int sig);

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
    char *args[2]; /* Arguments array */
    int status;
    char *path;

    args[0] = cmd;
    args[1] = NULL;

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
        if (strchr(cmd, '/') == NULL)
        {
            /* Use find_command if the command is not an absolute path */
            path = find_command(cmd);
            if (path == NULL)
            {
                fprintf(stderr, "%s: command not found\n", cmd);
                exit(EXIT_FAILURE);
            }
            execve(path, args, environ);
            free(path);
        }
        else
        {
            execve(cmd, args, environ);
        }
        perror("execve");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        waitpid(pid, &status, 0);
        return 0;
    }
}

/**
 * find_command - Finds the full path of a command
 * @command: The command to find
 *
 * Return: The full path of the command, or NULL if not found
 */
char *find_command(char *command)
{
    char *path = getenv("PATH");
    char *path_copy, *dir, *full_path;
    int length;

    if (path == NULL)
    {
        return NULL;
    }

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }

    length = strlen(path_copy) + strlen(command) + 2;
    full_path = malloc(length);
    if (full_path == NULL)
    {
        perror("malloc");
        free(path_copy);
        exit(EXIT_FAILURE);
    }

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        snprintf(full_path, length, "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    free(full_path);
    return NULL;
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

