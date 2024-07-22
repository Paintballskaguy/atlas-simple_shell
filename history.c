#include "shell.h"

/* History linked list */
/* External declarations of the head and tail of the command history linked list */
extern Command *historyHead;
extern Command *historyTail;

/**
 * add_history - Add a command to the history
 * @cmd: Command to add
 *
 * This function creates a copy of the provided command and adds it to the end 
 * of the command history linked list. It handles both the case where the list 
 * is empty and the case where the list already contains commands.
 */
void add_history(Command *cmd)
{
    /* Allocate memory for a new command */
    Command *newCmd = malloc(sizeof(Command));

    /* Copy the content of the provided command to the new command */
    memcpy(newCmd, cmd, sizeof(Command));
    newCmd->next = NULL;

    if (historyTail == NULL)
    {
        /* If the history list is empty, set both head and tail to the new command */
        historyHead = newCmd;
        historyTail = newCmd;
        newCmd->prev = NULL;
    }
    else
    {
        /* If the history list is not empty, add the new command to the end */
        historyTail->next = newCmd;
        newCmd->prev = historyTail;
        historyTail = newCmd;
    }
}

/**
 * print_history - Print the command history
 *
 * This function traverses the command history linked list from the head to 
 * the tail and prints each command along with its arguments, input and output 
 * redirections, and background execution status.
 */
void print_history(void)
{
    Command *temp = historyHead;
    int i = 1; /* Command number */
    int j;

    /* Traverse the command history linked list */
    while (temp != NULL)
    {
        printf("%d: ", i); /* Print the command number */
        
        /* Print all arguments of the command */
        for (j = 0; temp->args[j] != NULL; j++)
        {
            printf("%s ", temp->args[j]);
        }

        /* Print input redirection if any */
        if (temp->inputFile)
            printf("< %s ", temp->inputFile);

        /* Print output redirection if any */
        if (temp->outputFile)
            printf("> %s ", temp->outputFile);

        /* Print background execution status if any */
        if (temp->background)
            printf("&");

        printf("\n"); /* Print newline for the next command */
        temp = temp->next; /* Move to the next command */
        i++;
    }
}

/**
 * handle_sequence - Handle the sequence of commands
 * @cmd: Command to execute
 *
 * This function executes a command and, if the command is a sequence of commands, 
 * recursively executes the next command in the sequence.
 */
void handle_sequence(Command *cmd)
{
    /* Get the next command in the sequence */
    Command *nextCmd = cmd->next;

    /* Execute the current command */
    if (command_handler(cmd) == 1 && nextCmd != NULL)
    {
        /* If the current command executes successfully and there is a next command, execute it */
        handle_sequence(nextCmd);
    }
}
