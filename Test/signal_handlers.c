#include "shell.h"

void signal_handler_child(int p) {
    wait_child_processes();
    printf("\n");
}

void signal_handler_int(int p) {
    if (kill(pid, SIGTERM) == 0) {
        printf("\nProcess %d received a SIGINT signal\n", pid);
        no_reprint_prmpt = 1;
    } else {
        printf("\n");
    }
}
