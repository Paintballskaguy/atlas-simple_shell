#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void prompt(void);
void execute(char **argv);
char *trim_whitespace(char *str);

#endif /* SHELL_H */

