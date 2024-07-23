#include "shell.h"

void read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("$ ");
        read = getline(&line, &len, stdin);
        if (read == -1) {
            break;
        }
        printf("%s", line);
    }

    free(line);
}

