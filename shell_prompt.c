#include "shell.h"

/**
 * shell_prompt - Display the shell prompt
 */

void shell_prompt(void)
{
    char hostn[1204] = "";
    char *logname = NULL;
    int i;

    gethostname(hostn, sizeof(hostn));

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], "LOGNAME=", 8) == 0)
        {
            logname = environ[i] + 8;
            break;
        }
    }

    if (logname == NULL)
    {
        logname = "unknown";
    }

    printf("%s@%s %s > ", logname, hostn, getcwd(currentDirectory, 1024));
}
