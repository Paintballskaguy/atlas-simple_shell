#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t n = 0;
    char *args[1024]; /* Max args (adjust as needed) */
    ssize_t status;
    int i;

    while (1) {
        prompt();
        status = getline(&line, &n, stdin);
        if (status == -1) {
            break; /* Exit if getline fails (e.g., EOF) */
        }

        /* Tokenize input into arguments */
        args[0] = strtok(line, " \t\n");
        i = 1;
        while (args[i - 1] != NULL) {
            args[i] = strtok(NULL, " \t\n");
            i++;
        }

        /* Handle "exit" command */
        if (args[0] != NULL && strcmp(args[0], "exit") == 0) {
            break;
        }

        execute_command(args[0], args);
    }

    free(line);
    return 0;
}

