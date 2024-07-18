#include "shell.h"

int change_directory(char* args[]) {
    if (args[1] == NULL) {
        chdir(getenv("HOME"));
        return 1;
    } else {
        if (chdir(args[1]) == -1) {
            printf(" %s: no such directory\n", args[1]);
            return -1;
        }
    }
    return 0;
}
