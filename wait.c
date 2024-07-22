#include "wait_functions.h"

/**
 * waitpid_wrapper - A wrapper for the waitpid function
 * @pid: The process ID to wait for
 * @status: Pointer to an integer where the status will be stored
 * @options: Options for the waitpid function
 */

void waitpid_wrapper(pid_t pid, int *status, int options)
{
    waitpid(pid, status, options);
}

/**
 * wait_child_processes - Wait for all child processes to terminate
 */
void wait_child_processes(void)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
       ; /* No operation; just wait for child processes to terminate */
    }
}
