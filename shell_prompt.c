#include "shell.h"

char *get_custom_env(char *var)
{
    extern char **environ;
    int i;

    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], var, strlen(var)) == 0)
        {
            return environ[i] + strlen(var) + 1;
        }
    }
    return NULL;
}
