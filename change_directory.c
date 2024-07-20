#include "shell.h"

extern char **environ;
/**
 * change_directory - Change the current working directory
 * @args: Command arguments
 * Return: 1 on success, -1 on failure
 */

int change_directory(char *args[])
{
	char *home = NULL;
	int i;

    if (args[1] == NULL)
    {
        for (i = 0; environ[i] != NULL; i++)
        {
            if (strncmp(environ[i], "HOME=", 5) == 0)
            {
                home = environ[i] + 5;
                break;
            }
        }
        if (home)
        {
            chdir(home);
            return 1;
        }
        else
        {
            fprintf(stderr, "HOME not set\n");
            return -1;
        }
    }
    else
    {
        if (chdir(args[1]) == -1)
        {
            printf("%s: no such directory\n", args[1]);
            return -1;
        }
    }
    return 0;
}

