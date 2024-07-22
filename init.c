#include "shell.h"

/**
 * init - Initialize shell settings and environment
 */
void init(void)
{
    struct sigaction act_child; /* Signal action for child processes */
    struct sigaction act_int; /* Signal action for interrupt signal */

    GBSH_PID = getpid(); /* Get the shell's process ID */
    GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO); /* Check if the shell is running interactively */

    if (GBSH_IS_INTERACTIVE)
    {
        while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
            kill(GBSH_PID, SIGTTIN); /* Suspend the shell until it can become the foreground process group */

        /* Initialize act_child */
        memset(&act_child, 0, sizeof(struct sigaction));
        act_child.sa_handler = signal_handler_child;

        /* Initialize act_int */
        memset(&act_int, 0, sizeof(struct sigaction));
        act_int.sa_handler = signal_handler_int;

        sigaction(SIGCHLD, &act_child, 0); /* Register child signal handler */
        sigaction(SIGINT, &act_int, 0); /* Register interrupt signal handler */

        setpgid(GBSH_PID, GBSH_PID); /* Set the shell's process group ID */
        GBSH_PGID = getpgrp(); /* Get the shell's process group ID */

        if (GBSH_PID != GBSH_PGID)
        {
            printf("Error, the shell is not process group leader\n");
            exit(EXIT_FAILURE);
        }

        tcsetpgrp(STDIN_FILENO, GBSH_PGID); /* Set the shell as the foreground process group */
        tcgetattr(STDIN_FILENO, &GBSH_TMODES); /* Save the terminal modes */
    }

    currentDirectory = (char *)malloc(1024 * sizeof(char)); /* Allocate memory for the current directory */
    if (currentDirectory == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (getcwd(currentDirectory, 1024) == NULL)
    {
        perror("getcwd");
        free(currentDirectory);
        exit(EXIT_FAILURE);
    }
}
