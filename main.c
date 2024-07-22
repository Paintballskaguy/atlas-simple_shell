#include "shell.h"

extern char **environ; /* Environment variables */

/**
 * main - Entry point for the shell
 * Return: 0 on success, -1 on failure
 */
int main(void)
{
    char *line = NULL; /* Line read from input */
    size_t len = 0; /* Length of the line */
    ssize_t read; /* Number of characters read */
    Command *cmd; /* Command structure */

    init(); /* Initialize shell settings and environment */

    if (GBSH_IS_INTERACTIVE)
    {
        welcome_screen(); /* Display welcome screen if shell is interactive */
    }
    else
    {
        printf("Warning: shell is not running in an interactive mode (isatty failed).\n");
    }

    while (1)
    {
        cmd = malloc(sizeof(Command)); /* Allocate memory for a command structure */
        if (cmd == NULL)
        {
            perror("malloc"); /* Print error message if memory allocation fails */
            exit(EXIT_FAILURE); /* Exit with failure */
        }
        memset(cmd, 0, sizeof(Command)); /* Initialize the command structure to zero */

        if (GBSH_IS_INTERACTIVE)
        {
            shell_prompt(); /* Display the shell prompt */
        }

        read = getline(&line, &len, stdin); /* Read input from the user */
        if (read == -1)
        {
            if (errno == EINTR) /* Interrupted by signal */
            {
                free(cmd); /* Free the command structure */
                continue; /* Continue the loop */
            }
            else if (read == -1) /* Error or EOF */
            {
                free(cmd); /* Free the command structure */
                free(line); /* Free the line buffer */
                break; /* Exit the loop */
            }
        }

        line[read - 1] = '\0';  /* Remove newline character from the input line */
        tokenize(line, cmd); /* Tokenize the input line into the command structure */

        if (cmd->args[0] == NULL) /* Empty command */
        {
            free_command(cmd); /* Free the command structure */
            continue; /* Continue the loop */
        }

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
