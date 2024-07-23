#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t n = 0;
    char *args[2]; /* Array to store command and NULL */
    ssize_t status;

    while (1)
    {
        prompt();
        status = getline(&line, &n, stdin);
        if (status == -1)
        {
            if (feof(stdin)) /* Handle end of file (Ctrl+D) */
            {
                break;
            }
            perror("getline failed");
            continue;
        }

        /* Remove newline character from the input */
        if (line[status - 1] == '\n')
        {
            line[status - 1] = '\0';
        }

        /* Tokenize input into command */
        args[0] = strtok(line, " \t\n");
        args[1] = NULL;

        /* Handle empty input */
        if (args[0] == NULL)
        {
            continue;
        }

        /* Handle "exit" command */
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }

        execute_command(args);
    }

    free(line);
    return 0;
}

