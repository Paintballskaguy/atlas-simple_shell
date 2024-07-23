#include "shell.h"

void run_execve(void)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    printf("Before execve\n");
    if (execve(argv[0], argv, NULL) == -1) {
        perror("Error:");
    }
    printf("After execve\n");
}

