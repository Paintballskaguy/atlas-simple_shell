#include "shell.h"

/* Function prototypes */
char **environ; /* Environment variables */

/**
 * manage_environ - Manage environment variables
 * @args: Arguments from the command line
 * @option: Option to set or unset environment variables
 * 
 * Return: 0 on success, -1 on failure
 */
int manage_environ(char *args[], int option)
{
    if (option == 0)
    {
        /* Set an environment variable */
        if (args[1] == NULL || args[2] == NULL)
        {
            /* Check if sufficient arguments are provided */
            fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            return (-1);
        }

        /* Set environment variable using setenv() */
        if (setenv(args[1], args[2], 1) == -1)
        {
            /* Handle error */
            perror("setenv");
            return (-1);
        }
    }
    else if (option == 1)
    {
        /* Unset an environment variable */
        if (args[1] == NULL)
        {
            /* Check if sufficient arguments are provided */
            fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            return (-1);
        }

        /* Unset environment variable using unsetenv() */
        if (unsetenv(args[1]) == -1)
        {
            /* Handle error */
            perror("unsetenv");
            return (-1);
        }
    }
    else
    {
        /* Invalid option */
        fprintf(stderr, "Invalid option for manage_environ\n");
        return (-1);
    }

    /* Successful operation */
    return (0);
}
