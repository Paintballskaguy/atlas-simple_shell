#include "shell.h"

/* Global variables */
pid_t GBSH_PID;
pid_t GBSH_PGID;
struct termios GBSH_TMODES;
int GBSH_IS_INTERACTIVE;
char *currentDirectory;
pid_t pid;
int numTokens;
int no_reprint_prmpt = 0;

/* History linked list */
Command *historyHead = NULL;
Command *historyTail = NULL;

int main() 
{
    char line[MAXLINE];
    Command *cmd;
    numTokens = 0;

    init();
    welcome_screen();

    while (1) 
	{
        cmd = malloc(sizeof(Command));
        memset(cmd, 0, sizeof(Command));

        shell_prompt();
        memset(line, '\0', MAXLINE);
        fgets(line, MAXLINE, stdin);
        line[strlen(line) - 1] = '\n';
        tokenize(line, cmd);

        if (strcmp(cmd->args[0], "history") == 0) {
            print_history();
        } else {
            add_history(cmd);
            handle_sequence(cmd);
        }

        free_command(cmd);
    }

    free(currentDirectory);
    return 0;
}
