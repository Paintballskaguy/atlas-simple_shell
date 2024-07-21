#include "shell.h"

void free_command(Command *cmd)
{
    int i = 0;

    if (cmd)
    {
        while (cmd->args[i])
        {
            free(cmd->args[i]);
            i++;
        }

        free(cmd->inputFile);
        free(cmd->outputFile);
        free(cmd);
    }
}

