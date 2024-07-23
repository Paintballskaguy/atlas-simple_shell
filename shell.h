#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

void prompt(void);
void execute_command(char *command, char **args);

/* Function declarations */
void print_pid(void);
void print_ppid(void);
void read_line(void);
void print_args(int ac, char **av);
void run_execve(void);
void create_fork(void);
void wait_for_child(void);
void check_stat(int ac, char **av);
void print_env(char **env);

#endif /* SHELL_H */

