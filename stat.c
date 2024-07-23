#include "shell.h"

void check_stat(int ac, char **av)
{
    unsigned int i;
    struct stat st;

    if (ac < 2) {
        printf("Usage: stat path_to_file ...\n");
        return;
    }
    i = 1;
    while (av[i]) {
        printf("%s:", av[i]);
        if (stat(av[i], &st) == 0) {
            printf(" FOUND\n");
        } else {
            printf(" NOT FOUND\n");
        }
        i++;
    }
}

