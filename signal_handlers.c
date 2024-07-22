#include "shell.h"

/**
 * signal_handler_child - Handle SIGCHLD signal
 * @p: Signal number
 */
void signal_handler_child(int p)
{
	(void)p; /* Mark parameter as unused */
	wait_child_processes();
}

/**
 * signal_handler_int - Handle SIGINT signal
 * @p: Signal number
 */
void signal_handler_int(int p)
{
	extern pid_t pid;
	extern int no_reprint_prmpt;

	(void)p; /* Mark parameter as unused */

	if (kill(pid, SIGTERM) == 0)
	{
		printf("\nProcess %d received a SIGINT signal\n", pid);
	}
	no_reprint_prmpt = 1;
}
