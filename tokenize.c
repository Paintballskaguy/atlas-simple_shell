#include "shell.h"

/**
 * tokenize - Tokenizes a line into commands and arguments
 * @line: The line to tokenize
 * @cmd: The Command struct to fill
 */
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
