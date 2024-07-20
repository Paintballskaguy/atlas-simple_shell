#include "shell.h"
#include <unistd.h> /* Include this for fork, setpgid, getpgrp, etc. */
#include <signal.h> /* Include this for sigaction, SIGCHLD, etc. */
#include <termios.h> /* Include this for tcgetattr, tcsetattr, etc. */
#include <stdlib.h> /* Include this for calloc */
#include <stdio.h>

/**
 * init - Initialize the shell
 */
void init(void)
{
	struct sigaction act_child;
	struct sigaction act_int;

	GBSH_PID = getpid();
	GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);

	if (GBSH_IS_INTERACTIVE)
	{
		while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
		{
			kill(GBSH_PID, SIGTTIN);
		}

		act_child.sa_handler = signal_handler_child;
		act_int.sa_handler = signal_handler_int;
		sigemptyset(&act_child.sa_mask);
		sigemptyset(&act_int.sa_mask);
		act_child.sa_flags = 0;
		act_int.sa_flags = 0;

		if (sigaction(SIGCHLD, &act_child, NULL) == -1) {
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
		if (sigaction(SIGINT, &act_int, NULL) == -1) {
			perror("sigaction");
			exit(EXIT_FAILURE);
		}

		if (setpgid(GBSH_PID, GBSH_PID) < 0) {
			perror("setpgid");
			exit(EXIT_FAILURE);
		}
		GBSH_PGID = getpgrp();

		if (GBSH_PID != GBSH_PGID)
		{
			fprintf(stderr, "Error: the shell is not process group leader\n");
			exit(EXIT_FAILURE);
		}

		if (tcsetpgrp(STDIN_FILENO, GBSH_PGID) == -1) {
			perror("tcsetpgrp");
			exit(EXIT_FAILURE);
		}
		if (tcgetattr(STDIN_FILENO, &GBSH_TMODES) == -1) {
			perror("tcgetattr");
			exit(EXIT_FAILURE);
		}

		currentDirectory = (char *)calloc(1024, sizeof(char));
		if (currentDirectory == NULL) {
			perror("calloc");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "Error: shell is not running in an interactive mode (isatty failed).\n");
		exit(EXIT_FAILURE);
	}
}
