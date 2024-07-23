#include "shell.h"

void print_pid(void)
{
    pid_t my_pid;

    my_pid = getpid();
    printf("%u\n", my_pid);
}

