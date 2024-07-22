#include "shell.h"

/* External declaration of the environment variable array */
extern char **environ;

/**
 * change_directory - Change the current working directory
 * @args: Command arguments
 * Return: 1 on success, -1 on failure
 */
int change_directory(char *args[])
{
    /* Pointer to store the home directory path */
    char *home = NULL;
    int i;

    /* If no argument is provided, change to home directory */
    if (args[1] == NULL)
    {
        /* Iterate over the environment variables to find the HOME variable */
        for (i = 0; environ[i] != NULL; i++)
        {
            /* If the HOME variable is found, store its value */
            if (strncmp(environ[i], "HOME=", 5) == 0)
            {
                home = environ[i] + 5; /* Move pointer to the value part */
                break;
            }
        }
        /* If the HOME variable was found, change to the home directory */
        if (home)
        {
            chdir(home); /* Change directory to HOME */
            return 1;
        }
        else
        {
            /* If HOME is not set, print an error message */
            fprintf(stderr, "HOME not set\n");
            return -1;
        }
    }
    else
    {
        /* If an argument is provided, change to the specified directory */
        if (chdir(args[1]) == -1)
        {
            /* If changing directory fails, print an error message */
            printf("%s: no such directory\n", args[1]);
            return -1;
        }
    }
    return 0;
}
