#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

/* External declaration for environ */
extern char **environ;

/* Function prototypes */
void init(void);
void shell_prompt(void);
int command_handler(char *cmd);
char *find_command(char *command);
void handle_signal(int sig);

#endif /* SHELL_H */

