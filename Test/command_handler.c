#include "shell.h"

int command_handler(Command *cmd) {
    if (strcmp(cmd->args[0], "exit") == 0) exit(0);
    else if (strcmp(cmd->args[0], "pwd") == 0) {
        if (cmd->outputFile) {
            file_io(cmd, 0);
        } else {
            printf("%s\n", getcwd(currentDirectory, 1024));
        }
    } else if (strcmp(cmd->args[0], "clear") == 0) system("clear");
    else if (strcmp(cmd->args[0], "cd") == 0) change_directory(cmd->args);
    else if (strcmp(cmd->args[0], "environ") == 0) manage_environ(cmd->args, 0);
    else if (strcmp(cmd->args[0], "setenv") == 0) manage_environ(cmd->args, 1);
    else if (strcmp(cmd->args[0], "unsetenv") == 0) manage_environ(cmd->args, 2);
    else {
        if (cmd->inputFile || cmd->outputFile) {
            file_io(cmd, 1);
        } else {
            launch_prog(cmd);
        }
    }
    return 1;
}
