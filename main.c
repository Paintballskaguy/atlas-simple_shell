#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t n = 0;
    char *args[2]; /* Array to store command and NULL */
    ssize_t status;

    while (1)
    {
        if (isatty(STDIN_FILENO)) /* Check if input is from terminal */
        {
            prompt();
        }

        status = getline(&line, &n, stdin);
        if (status == -1)
        {
            if (feof(stdin)) /* Handle EOF */
            {
                free(line);
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
            free(line);
            exit(EXIT_SUCCESS);
        }

        execute_command(args);
    }

    free(line);
    return 0;
}

