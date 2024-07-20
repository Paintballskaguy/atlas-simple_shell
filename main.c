#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    Command *cmd;
    numTokens = 0;

    init();
    welcome_screen();

    while (1)
    {
        cmd = malloc(sizeof(Command));
        if (cmd == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memset(cmd, 0, sizeof(Command));

        shell_prompt();
        if (getline(&line, &len, stdin) == -1)
        {
            if (feof(stdin))
            {
                free(cmd);
                free(line);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                free(cmd);
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        tokenize(line, cmd);

        if (strcmp(cmd->args[0], "history") == 0)
        {
            print_history();
        }
        else
        {
            add_history(cmd);
            handle_sequence(cmd);
        }

        free_command(cmd);
    }

    free(currentDirectory);
    free(line);
    return 0;
}

