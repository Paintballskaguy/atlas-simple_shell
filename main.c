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
    char *argv[2];

    while (1)
    {
        prompt();

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin))
            {
                /* Handle EOF (Ctrl+D) */
                break;
            }
            perror("getline");
            continue;
        }

        /* Remove newline character from the input */
        line[read - 1] = '\0';

        if (strcmp(line, "exit") == 0)
        {
            break;
        }

        argv[0] = line;
        argv[1] = NULL;

        execute(argv);
    }

    free(line);
    return (0);
}
