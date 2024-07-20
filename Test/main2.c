#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1
#define FALSE !TRUE

// Function prototypes
char *command_generator(const char *text, int state);
char **command_completion(const char *text, int start, int end);
void execute_command(char *command);

int main(void)
{
    char *input, shell_prompt[100];

    // Configure readline to auto-complete
    rl_attempted_completion_function = command_completion;

    while (TRUE)
    {
        snprintf(shell_prompt, sizeof(shell_prompt), "turtleshell> ");

        // Display prompt and read input
        input = readline(shell_prompt);

        // Check for EOF
        if (!input)
        {
            break;
        }

        // Add input to history
        add_history(input);

        // Execute command
        execute_command(input);

        // Free the input
        free(input);
    }

    return 0;
}

char *command_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    // List of commands for completion
    static const char *commands[] = {
        "cd", "ls", "exit", "help", "history", NULL
    };

    if (!state)
    {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = (char *)commands[list_index++]))
    {
        if (strncmp(name, text, len) == 0)
        {
            return strdup(name);
        }
    }

    return NULL;
}

char **command_completion(const char *text, int start, int end)
{
    char **matches = NULL;

    // If this is a new word to complete, generate matches
    if (start == 0)
    {
        matches = rl_completion_matches(text, command_generator);
    }

    return matches;
}

void execute_command(char *command)
{
    // Split command into arguments
    char *args[100];
    int i = 0;

    args[i] = strtok(command, " ");
    while (args[i] != NULL)
    {
        args[++i] = strtok(NULL, " ");
    }

    // Handle built-in commands
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "turtleshell: expected argument to \"cd\"\n");
        }
        else
        {
            if (chdir(args[1]) != 0)
            {
                perror("turtleshell");
            }
        }
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        exit(0);
    }
    else
    {
        // For other commands, use fork and exec
        pid_t pid = fork();

        if (pid == 0)
        {
            // Child process
            if (execvp(args[0], args) == -1)
            {
                perror("turtleshell");
            }
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            // Error forking
            perror("turtleshell");
        }
        else
        {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }
}