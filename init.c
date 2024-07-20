#include "shell.h"

/**
 * init - Initialize the shell
 */

void init(void)
{
    struct sigaction act_child;
    struct sigaction act_int;

    printf("Initializing shell...\n");

    GBSH_PID = getpid();
    printf("Shell PID: %d\n", GBSH_PID);

    GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);
    printf("Interactive: %d\n", GBSH_IS_INTERACTIVE);

    if (GBSH_IS_INTERACTIVE)
    {
        while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
        {
            printf("Waiting for terminal control...\n");
            kill(GBSH_PID, SIGTTIN);
        }

        act_child.sa_handler = signal_handler_child;
        act_int.sa_handler = signal_handler_int;
        sigemptyset(&act_child.sa_mask);
        sigemptyset(&act_int.sa_mask);
        act_child.sa_flags = 0;
        act_int.sa_flags = 0;

        if (sigaction(SIGCHLD, &act_child, NULL) == -1) {
            perror("sigaction SIGCHLD");
            exit(EXIT_FAILURE);
        }
        if (sigaction(SIGINT, &act_int, NULL) == -1) {
            perror("sigaction SIGINT");
            exit(EXIT_FAILURE);
        }

        if (setpgid(GBSH_PID, GBSH_PID) < 0) {
            perror("setpgid");
            exit(EXIT_FAILURE);
        }
        GBSH_PGID = getpgrp();
        printf("Process group ID: %d\n", GBSH_PGID);

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

        currentDirectory = (char *)malloc(1024 * sizeof(char));
        if (currentDirectory == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memset(currentDirectory, 0, 1024 * sizeof(char));
    }
    else
    {
        fprintf(stderr, "Warning: shell is not running in an interactive mode (isatty failed).\n");
        /* Allow the shell to continue for testing purposes */
        currentDirectory = (char *)malloc(1024 * sizeof(char));
        if (currentDirectory == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memset(currentDirectory, 0, 1024 * sizeof(char));
    }
}

