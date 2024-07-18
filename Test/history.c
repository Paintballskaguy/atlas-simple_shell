#include "shell.h"

// History linked list
extern Command *historyHead;
extern Command *historyTail;

void add_history(Command *cmd) {
    Command *newCmd = malloc(sizeof(Command));
    memcpy(newCmd, cmd, sizeof(Command));
    newCmd->next = NULL;

    if (historyTail == NULL) {
        historyHead = newCmd;
        historyTail = newCmd;
        newCmd->prev = NULL;
    } else {
        historyTail->next = newCmd;
        newCmd->prev = historyTail;
        historyTail = newCmd;
    }
}

void print_history() {
    Command *temp = historyHead;
    int i = 1;
    while (temp != NULL) {
        printf("%d: ", i);
        for (int j = 0; temp->args[j] != NULL; j++) {
            printf("%s ", temp->args[j]);
        }
        if (temp->inputFile) printf("< %s ", temp->inputFile);
        if (temp->outputFile) printf("> %s ", temp->outputFile);
        if (temp->background) printf("&");
        printf("\n");
        temp = temp->next;
        i++;
    }
}

void free_command(Command *cmd) {
    // Clean up dynamically allocated Command struct
    free(cmd);
}

void handle_sequence(Command *cmd) {
    Command *nextCmd = cmd->next;
    if (command_handler(cmd) == 1 && nextCmd != NULL) {
        handle_sequence(nextCmd);
    }
}
