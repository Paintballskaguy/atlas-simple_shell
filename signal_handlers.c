#include "shell.h"

void signal_handler_child(int p)
{
    wait_child_processes();
}

void signal_handler_int(int p)
{
    extern pid_t pid;
    extern int no_reprint_prmpt;

    if (kill(pid, SIGTERM) == 0)
    {
        printf("\nProcess %d received a SIGINT signal\n", pid);
    }
    no_reprint_prmpt = 1;
}
