#include "shell.h"

void tokenize(char *line, Command *cmd) {
    int i = 0;
    numTokens = 0;
    char *token = strtok(line, " \t\r\n\a");

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\r\n\a");
            cmd->inputFile = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\r\n\a");
            cmd->outputFile = token;
        } else if (strcmp(token, "&") == 0) {
            cmd->background = 1;
        } else {
            cmd->args[i] = token;
            i++;
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    cmd->args[i] = NULL;
    numTokens = i;
}
