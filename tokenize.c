#include "shell.h"

/**
 * tokenize - Tokenize the input line into command and arguments
 * @line: Input line to tokenize
 * @cmd: Command structure to populate
 */

void tokenize(char *line, Command *cmd)
{
	int i = 0;
	char *token;

	numTokens = 0;
	token = strtok(line, " \t\r\n\a");

	while (token != NULL)
	{
		if (strcmp(token, "<") == 0)
		{
			token = strtok(NULL, " \t\r\n\a");
			cmd->inputFile = token;
		}
		else if (strcmp(token, ">") == 0)
		{
			token = strtok(NULL, " \t\r\n\a");
			cmd->outputFile = token;
		}
		else if (strcmp(token, "&") == 0)
		{
			cmd->background = 1;
		}
		else
		{
			if (i < LIMIT - 1)
			{
			cmd->args[i] = token;
			i++;
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	cmd->args[i] = NULL;
	numTokens = i;
}
