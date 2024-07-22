#include "shell.h"

/**
 * tokenize - Tokenizes a line into commands and arguments
 * @line: The line to tokenize
 * @cmd: The Command struct to fill
 *
 * This function takes a line of input and breaks it down into individual tokens,
 * which are then stored as arguments in the Command struct. It uses the strtok
 * function to split the line based on delimiters such as spaces, tabs, carriage 
 * returns, newlines, and alert characters.
 */
void tokenize(char *line, Command *cmd)
{
    int position = 0; /* Position in the args array */
    char *token; /* Pointer to the current token */

    /* Get the first token */
    token = strtok(line, " \t\r\n\a");
    
    /* Continue to tokenize the line */
    while (token != NULL)
    {
        /* Duplicate the token and store it in the args array */
        cmd->args[position] = strdup(token);
        
        /* Check if memory allocation for the token failed */
        if (cmd->args[position] == NULL)
        {
            perror("strdup"); /* Print an error message */
            exit(EXIT_FAILURE); /* Exit the program with failure status */
        }
        
        position++; /* Move to the next position in the args array */
        
        /* Get the next token */
        token = strtok(NULL, " \t\r\n\a");
    }
    
    /* Null-terminate the args array */
    cmd->args[position] = NULL;
}
