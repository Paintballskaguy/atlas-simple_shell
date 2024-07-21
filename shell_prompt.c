#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

char *get_custom_env(const char *name)
{
	int i;

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(name, environ[i], strlen(name)) == 0 && environ[i][strlen(name)] == '=')
        {
            return environ[i] + strlen(name) + 1;
        }
    }
    return NULL;
}

/**
 * shell_prompt - Display the shell prompt
 */
void shell_prompt(void)
{
    char hostn[1204] = "";

    gethostname(hostn, sizeof(hostn));
    printf("%s@%s %s > ", get_custom_env("LOGNAME"), hostn, getcwd(currentDirectory, 1024));
}

