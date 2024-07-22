#include "shell.h"

extern char **environ;

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    Command *cmd;

    init();

    if (GBSH_IS_INTERACTIVE)
    {
        welcome_screen();
    }
    else
    {
        printf("Warning: shell is not running in an interactive mode (isatty failed).\n");
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
            if (errno == EINTR)
            {
                free(cmd);
                continue;
            }
            else if (read == -1)
            {
                free(cmd);
                free(line);
                break;
            }
        }

        line[read - 1] = '\0';
        tokenize(line, cmd);

        if (cmd->args[0] == NULL)
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

