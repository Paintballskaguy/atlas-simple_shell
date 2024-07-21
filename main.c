#include "shell.h"

extern char **environ;

/**
 * main - Entry point for the shell
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    Command *cmd;
    numTokens = 0;

    init();

    if (GBSH_IS_INTERACTIVE)
    {
        welcome_screen();
    }

    while (1)
    {
        cmd = malloc(sizeof(Command));
        if (cmd == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memset(cmd, 0, sizeof(Command));

        if (GBSH_IS_INTERACTIVE)
        {
            shell_prompt();
        }

        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            if (feof(stdin)) /* End of file (Ctrl+D) */
            {
                free(cmd);
                free(line);
                break;
            }
            else if (errno == EINTR) /* Interrupted by signal */
            {
                continue;
            }
            else
            {
                perror("getline");
                free(cmd);
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        tokenize(line, cmd);

        if (cmd->args[0] == NULL) /* Empty command */
        {
            free_command(cmd);
            continue;
        }

        if (strcmp(cmd->args[0], "history") == 0)
        {
            print_history();
        }
        else
        {
            add_history(cmd);
            handle_sequence(cmd);
        }

        free_command(cmd);
    }

    free(currentDirectory);
    free(line);
    return 0;
}

