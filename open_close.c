#include "shell.h"

pid_t terminal_pid = 0; 

/**
 * open_new_terminal - opens a new terminal window.
 */

void open_new_terminal(void)
{
	terminal_pid = fork();
	if (terminal_pid == 0)
	{
		execlp("gnome-terminal", "gnome-terminal", "--", "/bin/bash", (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else if (terminal_pid < 0) /* fork failed */
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}


/**
 * close_terminal - closes the new terminal when exit is successful.
 */

void close_terminal(void)
{
	if (terminal_pid > 0)
	{
		kill(terminal_pid, SIGTERM);
	}
}