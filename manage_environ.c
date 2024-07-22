#include "shell.h"

extern char **environ; /* Environment variables */

/**
 * main - Entry point for the shell
 * Return: 0 on success, -1 on failure
 */
int main(void)
{
    char *line = NULL; /* Line read from input */
    size_t len = 0; /* Length of the line buffer */
    ssize_t read; /* Number of characters read */
    Command *cmd; /* Command structure */

    init(); /* Initialize shell settings and environment */

    /* Check if the shell is in interactive mode */
    if (GBSH_IS_INTERACTIVE)
    {
        welcome_screen(); /* Display welcome screen if shell is interactive */
    }
    else
    {
        printf("Warning: shell is not running in an interactive mode (isatty failed).\n");
    }

    /* Main loop to read and process commands */
    while (1)
    {
        /* Allocate memory for a command structure */
        cmd = malloc(sizeof(Command));
        if (cmd == NULL)
        {
            perror("malloc"); /* Print error message if memory allocation fails */
            exit(EXIT_FAILURE); /* Exit with failure */
        }
        memset(cmd, 0, sizeof(Command)); /* Initialize the command structure to zero */

        /* Display the shell prompt if in interactive mode */
        if (GBSH_IS_INTERACTIVE)
        {
            shell_prompt();
        }

        /* Read input from the user */
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (errno == EINTR) /* If interrupted by a signal */
            {
                free(cmd); /* Free the command structure */
                continue; /* Continue the loop */
            }
            else if (read == -1) /* If error or EOF */
            {
                free(cmd); /* Free the command structure */
                free(line); /* Free the line buffer */
                break; /* Exit the loop */
            }
        }

        line[read - 1] = '\0';  /* Remove newline character from the input line */
        tokenize(line, cmd); /* Tokenize the input line into the command structure */

        /* If the command is empty, free the command structure and continue */
        if (cmd->args[0] == NULL)
        {
            free_command(cmd);
            continue;
        }

        /* Check if the command is "history" */
        if (strcmp(cmd->args[0], "history") == 0)
        {
            print_history(); /* Print command history if "history" command is entered */
        }
        else
        {
            add_history(cmd); /* Add the command to the history */
            handle_sequence(cmd); /* Handle the command sequence */
        }

        free_command(cmd); /* Free the command structure */
    }

    free(currentDirectory); /* Free the current directory string */
    free(line); /* Free the line buffer */
    return 0; /* Return success */
}
