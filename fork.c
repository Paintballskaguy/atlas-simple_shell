#include "shell.h"

void create_fork(void)
{
    pid_t my_pid;
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Error:");
        return;
    }
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    if (child_pid == 0) {
        printf("(%u) Nooooooooo!\n", my_pid);
    } else {
        printf("(%u) %u, I am your father\n", my_pid, child_pid);
    }
}

