#include "shell.h"

/* Global variables */
pid_t GBSH_PID;
pid_t GBSH_PGID;
struct termios GBSH_TMODES;
int GBSH_IS_INTERACTIVE;
char *currentDirectory = NULL;
pid_t pid;
int numTokens;
int no_reprint_prmpt;

/* Command history */
Command *historyHead = NULL;
Command *historyTail = NULL;

