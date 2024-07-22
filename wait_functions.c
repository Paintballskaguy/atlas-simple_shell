#include "wait_functions.h"

void waitpid_wrapper(pid_t pid, int *status, int options)
{
    waitpid(pid, status, options);
}

void wait_child_processes(void)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
        ; /* No operation; just wait for child processes to terminate */
    }
}

