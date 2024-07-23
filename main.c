#include "shell.h"

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
    char *original_line = NULL;

    while (1)
    {
        prompt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            /* Handle EOF (Ctrl+D) */
            if (line)
                free(line);
            break;
        }

        /* Remove newline character from the input */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        /* Trim leading and trailing spaces */
        original_line = line;
        line = trim_whitespace(line);

		  /* Skip empty input */
        if (line[0] == '\0')
        {
            free(original_line);
            continue;
        }

        if (strcmp(line, "exit") == 0)
        {
            free(original_line);
            break;
        }

        /* Split the line into arguments */
        argv = split_line(line);

        execute(argv);

        free(argv);
        free(original_line);
        line = NULL;  /* Reset line to NULL to prevent double free */
    }

    return (0);
}