#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

#define MAXLINE 1024

extern char **environ;

void init(void);
void shell_prompt(void);
int command_handler(char *cmd);
void handle_signal(int sig);
void tokenize(char *line, char **args);
void signalHandler_child(int p);
void signalHandler_int(int p);
int changeDirectory(char *args[]);

int is_interactive;
static pid_t GBSH_PID, GBSH_PGID;
static struct termios GBSH_TMODES;
static char *currentDirectory;

/**
 * init - Initialize the shell
 */
void init(void)
{
    signal(SIGINT, handle_signal);
    signal(SIGCHLD, signalHandler_child);
    is_interactive = isatty(STDIN_FILENO);
    GBSH_PID = getpid();

    if (is_interactive)
    {
        while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
            kill(GBSH_PID, SIGTTIN);
        setpgid(GBSH_PID, GBSH_PID);
        GBSH_PGID = getpgrp();
        if (GBSH_PID != GBSH_PGID)
        {
            fprintf(stderr, "Error: shell is not the process group leader.\n");
            exit(EXIT_FAILURE);
        }
        tcsetpgrp(STDIN_FILENO, GBSH_PGID);
        tcgetattr(STDIN_FILENO, &GBSH_TMODES);
    }
    currentDirectory = (char *)calloc(1024, sizeof(char));
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
            printf("\n");
            shell_prompt();
            fflush(stdout);
        }
    }
}

/**
 * signalHandler_child - Handle SIGCHLD signal
 * @p: Signal number
 */
void signalHandler_child(int p)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

/**
 * shell_prompt - Display the shell prompt
 */
void shell_prompt(void)
{
    if (is_interactive)
    {
        printf("%s@%s %s > ", getenv("LOGNAME"), getenv("HOSTNAME"), getcwd(currentDirectory, 1024));
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
    char *args[MAXLINE / 2 + 1];
    int status;

    tokenize(cmd, args);

    if (args[0] == NULL)
        return 1;

    if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        printf("%s\n", getcwd(currentDirectory, 1024));
    }
    else if (strcmp(args[0], "clear") == 0)
    {
        system("clear");
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        changeDirectory(args);
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        printf("./shell: No such file or directory\n");
    }
    else
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return -1;
        }
        else if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}

/**
 * changeDirectory - Change directory
 * @args: Arguments array
 *
 * Return: 0 on success, -1 on failure
 */
int changeDirectory(char *args[])
{
    if (args[1] == NULL)
    {
        chdir(getenv("HOME"));
        return 1;
    }
    else if (chdir(args[1]) == -1)
    {
        printf(" %s: no such directory\n", args[1]);
        return -1;
    }
    return 0;
}

/**
 * tokenize - Tokenize input string into arguments
 * @line: Input string
 * @args: Arguments array
 */
void tokenize(char *line, char **args)
{
    int i = 0;
    char *token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n\a");
    }
    args[i] = NULL;
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

    init();

    while (1)
    {
        shell_prompt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (errno == EINTR)
            {
                clearerr(stdin);
                continue;
            }
            else
            {
                printf("\n");
                break;
            }
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (line[0] == '\0')
            continue;

        command_handler(line);
    }

    free(line);
    return 0;
}
