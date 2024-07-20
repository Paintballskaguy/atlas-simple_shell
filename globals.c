#include "shell.h"

/* Global variables */
pid_t GBSH_PID;
pid_t GBSH_PGID;
struct termios GBSH_TMODES;
int GBSH_IS_INTERACTIVE;
char *currentDirectory;
pid_t pid;
int numTokens;
int no_reprint_prmpt;

/* Command history */
Command *historyHead = NULL;
Command *historyTail = NULL;

/* Signal handlers */
struct sigaction act_child;
struct sigaction act_int;

