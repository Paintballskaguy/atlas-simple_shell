#include "shell.h"

/**
 * signal_handler_child - Handle SIGCHLD signal
 * @p: Signal number
 *
 * This function is a signal handler for the SIGCHLD signal, which is sent to 
 * the parent process whenever a child process terminates. It calls the 
 * wait_child_processes function to clean up any terminated child processes.
 */
void signal_handler_child(int p)
{
    (void)p; /* Mark parameter as unused to avoid compiler warning */

    wait_child_processes(); /* Clean up terminated child processes */
}

/**
 * signal_handler_int - Handle SIGINT signal
 * @p: Signal number
 *
 * This function is a signal handler for the SIGINT signal, which is typically
 * sent when the user presses Ctrl+C. It attempts to terminate the current 
 * child process, if any, and sets a flag to reprint the prompt.
 */
void signal_handler_int(int p)
{
    extern pid_t pid; /* Current child process ID */
    extern int no_reprint_prmpt; /* Flag to control prompt reprinting */

    (void)p; /* Mark parameter as unused to avoid compiler warning */

    /* Attempt to terminate the current child process */
    if (kill(pid, SIGTERM) == 0)
    {
        /* If successful, print a message indicating the process was terminated */
        printf("\nProcess %d received a SIGINT signal\n", pid);
    }
    
    /* Set the flag to indicate that the prompt should be reprinted */
    no_reprint_prmpt = 1;
}
