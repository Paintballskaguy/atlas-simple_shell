#ifndef WAIT_FUNCTIONS_H
#define WAIT_FUNCTIONS_H

#include <sys/types.h>

pid_t waitpid_wrapper(pid_t pid, int *status, int options);
void wait_child_processes();

#endif  /* WAIT_FUNCTIONS_H */
