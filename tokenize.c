#include "shell.h"

void tokenize(char *line, Command *cmd)
{
    int position = 0;
    char *token;

    token = strtok(line, " \t\r\n\a");
    while (token != NULL)
    {
        cmd->args[position] = strdup(token);
        if (cmd->args[position] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        position++;
        token = strtok(NULL, " \t\r\n\a");
    }
    cmd->args[position] = NULL;
}

