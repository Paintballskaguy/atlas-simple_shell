#include "shell.h"

void shell_prompt() {
    char hostn[1204] = "";
    gethostname(hostn, sizeof(hostn));
    printf("%s@%s %s > ", getenv("LOGNAME"), hostn, getcwd(currentDirectory, 1024));
}
