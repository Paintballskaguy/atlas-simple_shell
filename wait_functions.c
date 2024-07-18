#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

pid_t waitpid_wrapper(pid_t pid, int *status, int options) {
    pid_t result = waitpid(pid, status, options);
    if (result == -1 && errno != ECHILD) {
        perror("waitpid");
    }
    return result;
}

void wait_child_processes() {
    while (waitpid(-1, NULL, WNOHANG) > 0) {}
}
