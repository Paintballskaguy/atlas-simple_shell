#include "shell.h"
#include <stdio.h>
#include <string.h>

extern char **environ;

/**
 * manage_environ - Manage environment variables
 * @args: Command arguments
 * @option: Option to set or unset environment variables
 * Return: 0 on success, -1 on failure
 */

int manage_environ(char *args[], int option)
{
    char **env_aux;
    int i;

    switch (option) {
        case 0:
            for (env_aux = environ; *env_aux != 0; env_aux++)
            {
                printf("%s\n", *env_aux);
            }
            break;
        case 1:
            if ((args[1] == NULL) && args[2] == NULL)
            {
                printf("%s", "Not enough input arguments\n");
                return -1;
            }

            for (i = 0; environ[i] != NULL; i++)
            {
                if (strncmp(environ[i], args[1], strlen(args[1])) == 0 && environ[i][strlen(args[1])] == '=')
                {
                    printf("%s", "The variable has been overwritten\n");
                    break;
                }
            }

            if (args[2] == NULL)
            {
                setenv(args[1], "", 1);
            }
            else
            {
                setenv(args[1], args[2], 1);
            }
            break;
        case 2:
            if (args[1] == NULL)
            {
                printf("%s", "Not enough input arguments\n");
                return -1;
            }
            if (unsetenv(args[1]) == 0)
            {
                printf("%s", "The variable has been erased\n");
            }
            else
            {
                printf("%s", "The variable does not exist\n");
            }
            break;
    }
    return 0;
}

