#include "shell.h"

/* External declarations for the history linked list */
extern Command *historyHead;
extern Command *historyTail;

/**
 * add_history - Add a command to the history
 * @cmd: Command to add
 */
void add_history(Command *cmd)
{
    Command *newCmd = malloc(sizeof(Command));

    memcpy(newCmd, cmd, sizeof(Command));
    newCmd->next = NULL;

    if (historyTail == NULL)
    {
        historyHead = newCmd;
        historyTail = newCmd;
        newCmd->prev = NULL;
    }
    else
    {
        historyTail->next = newCmd;
        newCmd->prev = historyTail;
        historyTail = newCmd;
    }
}

/**
 * print_history - Print the command history
 */
void print_history(void)
{
    Command *temp = historyHead;
    int i = 1;
    int j;

    while (temp != NULL)
    {
        printf("%d: ", i);
        for (j = 0; temp->args[j] != NULL; j++)
        {
            printf("%s ", temp->args[j]);
        }
        if (temp->inputFile)
            printf("< %s ", temp->inputFile);
        if (temp->outputFile)
            printf("> %s ", temp->outputFile);
        if (temp->background)
            printf("&");
        printf("\n");
        temp = temp->next;
        i++;
    }
}

/**
 * handle_sequence - Handle the sequence of commands
 * @cmd: Command to execute
 */
void handle_sequence(Command *cmd)
{
    Command *nextCmd = cmd->next;

    if (command_handler(cmd) == 1 && nextCmd != NULL)
    {
        handle_sequence(nextCmd);
    }
}

