#include "shell.h"

/**
 * init - Initializes the shell, sets terminal settings for interactive mode
 *
 * This function sets up the initial state of the shell, including setting up
 * signal handlers, terminal settings, and determining if the shell is running
 * in interactive mode.
 */
void init()
{
    struct sigaction act_child; /* Structure for SIGCHLD signal handling */
    struct sigaction act_int;   /* Structure for SIGINT signal handling */

    /* Get the process ID of the shell */
    GBSH_PID = getpid();
    
    /* Check if the shell is running in interactive mode */
    GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);

    if (GBSH_IS_INTERACTIVE)
    {
        /* Ensure the shell is the foreground process in its process group */
        while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
            kill(GBSH_PID, SIGTTIN); /* Suspend the shell until it becomes the foreground process group */

        /* Set up the signal handlers */
        act_child.sa_handler = signal_handler_child;
        act_int.sa_handler = signal_handler_int;

        /* Register the signal handlers */
        sigaction(SIGCHLD, &act_child, 0); /* Handle child process termination */
        sigaction(SIGINT, &act_int, 0);    /* Handle interrupt signal (Ctrl+C) */

        /* Set the shell as its own process group leader */
        setpgid(GBSH_PID, GBSH_PID);
        GBSH_PGID = getpgrp();

        /* Check if setting the process group was successful */
        if (GBSH_PID != GBSH_PGID)
        {
            printf("Error, the shell is not process group leader\n");
            exit(EXIT_FAILURE);
        }

        /* Make the shell the foreground process */
        tcsetpgrp(STDIN_FILENO, GBSH_PGID);
        
        /* Save the current terminal attributes */
        tcgetattr(STDIN_FILENO, &GBSH_TMODES);
    }

    /* Allocate memory for the current working directory */
    currentDirectory = (char *)malloc(1024 * sizeof(char));
    if (currentDirectory == NULL)
    {
        /* Handle memory allocation failure */
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Get the current working directory */
    if (getcwd(currentDirectory, 1024) == NULL)
    {
        /* Handle failure to get the current working directory */
        perror("getcwd");
        free(currentDirectory);
        exit(EXIT_FAILURE);
    }
}
