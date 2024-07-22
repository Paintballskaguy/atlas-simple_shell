#include "shell.h"

void init()
{
    struct sigaction act_child;
    struct sigaction act_int;

    GBSH_PID = getpid();
    GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);

    if (GBSH_IS_INTERACTIVE)
    {
        while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
            kill(GBSH_PID, SIGTTIN);

        act_child.sa_handler = signal_handler_child;
        act_int.sa_handler = signal_handler_int;

        sigaction(SIGCHLD, &act_child, 0);
        sigaction(SIGINT, &act_int, 0);

        setpgid(GBSH_PID, GBSH_PID);
        GBSH_PGID = getpgrp();

        if (GBSH_PID != GBSH_PGID)
        {
            printf("Error, the shell is not process group leader\n");
            exit(EXIT_FAILURE);
        }

        tcsetpgrp(STDIN_FILENO, GBSH_PGID);
        tcgetattr(STDIN_FILENO, &GBSH_TMODES);
    }

    currentDirectory = (char *)malloc(1024 * sizeof(char));
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
