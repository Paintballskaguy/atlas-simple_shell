#include "shell.h"

void wait_for_child(void)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("Error:");
        return;
    }
    if (child_pid == 0) {
        printf("Wait for me, wait for me\n");
        sleep(3);
    } else {
        wait(&status);
        printf("Oh, it's all better now\n");
    }
}

