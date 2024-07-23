#include "shell.h"

void execute_command(char *command, char **args)
{
    pid_t child_pid;

    if (command == NULL) {
        return;
    }

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (child_pid == 0) {
        if (execve(command, args, environ) == -1) {
            perror("./hsh");
            exit(1);
        }
    } else {
        wait(NULL);
    }
}

