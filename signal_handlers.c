#include "shell.h"

/**
 * signal_handler_child - Handle SIGCHLD signal
 * @p: Signal number
 */

void signal_handler_child(int p)
{
	(void)p; /* Mark the parameter as unused to avoid warning */
	wait_child_processes();
	printf("\n");
}

/**
 * signal_handler_int - Handle SIGINT signal
 * @p: Signal number
 */
void signal_handler_int(int p)
{
	(void)p; /* Mark the parameter as unused to avoid warning */
	if (kill(pid, SIGTERM) == 0)
	{
		printf("\nProcess %ld received a SIGINT signal\n", (long)pid);
		no_reprint_prmpt = 1;
	}
	else
	{
		printf("\n");
	}
}
