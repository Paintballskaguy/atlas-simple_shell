#include "shell.h"

extern char **environ;

/**
 * print_env - Prints the current environment variables
 */
void print_env(void)
{
    char **env = environ;

    while (*env)
    {
        printf("%s\n", *env);
        env++;
    }
}

/**
 * main - Entry point of the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **argv;
    char *trimmed_line;
    int status = 0;

    while (1)
    {
        prompt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            /* Handle EOF (Ctrl+D) */
            free(line);
            break;
        }

        /* Remove newline character from the input */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Trim leading and trailing spaces */
        trimmed_line = trim_whitespace(line);

        /* Skip empty input */
        if (trimmed_line[0] == '\0')
        {
            continue;
        }

        if (strcmp(trimmed_line, "exit") == 0)
        {
            break;
        }

        if (strcmp(trimmed_line, "env") == 0)
        {
            print_env();
            continue;
        }

        /* Split the line into arguments */
        argv = split_line(trimmed_line);
        if (argv == NULL)
        {
            perror("split_line");
            continue;
        }

        status = execute(argv);

        free(argv);
    }

    free(line);
    return status;
}
