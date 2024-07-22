#include "shell.h"

/* Global variable to store the process ID of the shell */
pid_t GBSH_PID;

/* Global variable to store the process group ID of the shell */
pid_t GBSH_PGID;

/* Global variable to store the terminal modes of the shell */
struct termios GBSH_TMODES;

/* Global variable to check if the shell is running in interactive mode */
int GBSH_IS_INTERACTIVE;

/* Global variable to store the current directory */
char *currentDirectory = NULL;

/* Global variable to store the process ID for child processes */
pid_t pid;

/* Global variable to store the number of tokens in a command */
int numTokens;

/* Global variable to indicate if the prompt should be reprinted */
int no_reprint_prmpt;

/* Command History */
/* Pointer to the head of the command history linked list */
Command *historyHead = NULL;

/* Pointer to the tail of the command history linked list */
Command *historyTail = NULL;

/* Signal handlers */
/* Structure to define the action taken for SIGCHLD signal */
struct sigaction act_child;

/* Structure to define the action taken for SIGINT signal */
struct sigaction act_int;
