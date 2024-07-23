#include "shell.h"

void print_env(char **env)
{
    unsigned int i;

    i = 0;
    while (env[i] != NULL) {
        printf("%s\n", env[i]);
        i++;
    }
}

