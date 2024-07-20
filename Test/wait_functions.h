#ifndef WAIT_FUNCTIONS_H
#define WAIT_FUNCTIONS_H

#include <sys/types.h>
#include <sys/wait.h>

void waitpid_wrapper(pid_t pid, int *status, int options);
void wait_child_processes(void);

#endif /* WAIT_FUNCTIONS_H */
