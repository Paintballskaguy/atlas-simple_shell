#include "shell.h"

void print_args(int ac, char **av)
{
    int i = 0;
    (void)ac;  /* Cast ac to void to avoid unused parameter warning */
    while (av[i] != NULL) {
        printf("%s\n", av[i]);
        i++;
    }
}

