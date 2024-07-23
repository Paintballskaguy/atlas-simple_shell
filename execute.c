#include "shell.h"

void execute_command(char *command, char **args)
{
    pid_t child_pid;

    if (command == NULL) {
        return;
    }

    /* Match command to functions */
    if (strcmp(command, "pid") == 0) {
        print_pid();
        return;
    } else if (strcmp(command, "ppid") == 0) {
        print_ppid();
        return;
    } else if (strcmp(command, "getline") == 0) {
        read_line();
        return;
    } else if (strcmp(command, "args") == 0) {
        print_args(0, NULL); /* Adjust arguments as needed */
        return;
    } else if (strcmp(command, "execve") == 0) {
        run_execve();
        return;
    } else if (strcmp(command, "fork") == 0) {
        create_fork();
        return;
    } else if (strcmp(command, "wait") == 0) {
        wait_for_child();
        return;
    } else if (strcmp(command, "stat") == 0) {
        check_stat(0, NULL); /* Adjust arguments as needed */
        return;
    } else if (strcmp(command, "printenv") == 0) {
        print_env(environ);
        return;
    }

    /* Default fork and execve if not a special command */
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (child_pid == 0) {
        if (execve(command, args, environ) == -1) {
            perror("./hsh");
            exit(1);
        }
    } else {
        wait(NULL);
    }
}

