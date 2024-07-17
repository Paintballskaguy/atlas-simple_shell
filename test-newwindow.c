#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BUFFER_SIZE 1024

void launch_new_window(char *command);

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *args[10]; // You can adjust this size as needed
	int i;

	while (1)
	{
		printf("simple_shell> ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			perror("fgets");
			continue;
		}

		// Remove trailing newline character
		buffer[strcspn(buffer, "\n")] = 0;

		if (strcmp(buffer, "exit") == 0)
			break;

		// Tokenize the input string
		char *token = strtok(buffer, " ");
		i = 0;
		while (token != NULL && i < 10)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;

		if (i > 0 && strcmp(args[0], "launch") == 0)
		{
			launch_new_window(args[1]);
		}
		else
		{
			// Construct the command line string
			char command[BUFFER_SIZE] = "";
			for (int j = 0; j < i; j++)
			{
				strcat(command, args[j]);
				if (j < i - 1)
					strcat(command, " ");
			}

			// Execute the command
			system(command);
		}
	}

	return 0;
}

void launch_new_window(char *command)
{
	if (command == NULL)
	{
		fprintf(stderr, "Usage: launch <command>\n");
		return;
	}

	char cmd_command[BUFFER_SIZE];
	snprintf(cmd_command, sizeof(cmd_command), "start cmd /c \"%s\"", command);
	system(cmd_command);
}
