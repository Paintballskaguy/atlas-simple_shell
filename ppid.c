#include "shell.h"

void print_ppid(void)
{
    pid_t parent_pid;

    parent_pid = getppid();
    printf("%u\n", parent_pid);
}

