#include "wait_functions.h"

/**
 * waitpid_wrapper - A wrapper for the waitpid function
 * @pid: The process ID to wait for
 * @status: Pointer to an integer where the status will be stored
 * @options: Options for the waitpid function
 *
 * This function is a simple wrapper around the waitpid system call.
 * It waits for the process with the specified PID to change state.
 * The status of the process is stored in the provided status variable.
 * The options parameter specifies additional options for the waitpid call.
 */
void waitpid_wrapper(pid_t pid, int *status, int options)
{
    waitpid(pid, status, options); /* Call the waitpid function with the given arguments */
}

/**
 * wait_child_processes - Wait for all child processes to terminate
 *
 * This function uses a loop to repeatedly call waitpid in non-blocking mode
 * (WNOHANG) to reap any child processes that have terminated. The loop continues
 * until there are no more child processes to reap (waitpid returns 0 or -1).
 */
void wait_child_processes(void)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
       ; /* No operation; just wait for child processes to terminate */
    }
}
