#include "shell.h"

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The line to be split
 *
 * Return: An array of tokens
 */

char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE;						  /* Initial buffer size for tokens */
	int position = 0;								  /* Position in the tokens array */
	char **tokens = malloc(bufsize * sizeof(char *)); /* Allocate memory for tokens */
	char *token;									  /* Token pointer */

	if (!tokens) /* Check if memory allocation failed */
	{
		fprintf(stderr, "hsh: allocation error\n"); /* Print error message */
		exit(EXIT_FAILURE);							/* Exit with failure status */
	}

	token = strtok(line, TOK_DELIM); /* Tokenize the line using delimiters */
	while (token != NULL)			 /* Loop through each token */
	{
		tokens[position] = token; /* Store the token in the tokens array */
		position++;

		if (position >= bufsize) /* Check if the position exceeds the buffer size */
		{
			bufsize += TOK_BUFSIZE;								/* Increase the buffer size */
			tokens = realloc(tokens, bufsize * sizeof(char *)); /* Reallocate memory for tokens */
			if (!tokens)										/* Check if memory reallocation failed */
			{
				fprintf(stderr, "hsh: allocation error\n"); /* Print error message */
				exit(EXIT_FAILURE);							/* Exit with failure status */
			}
		}

		token = strtok(NULL, TOK_DELIM); /* Continue tokenizing the line */
	}
	tokens[position] = NULL; /* Null-terminate the tokens array */
	return tokens;			 /* Return the tokens array */
}
