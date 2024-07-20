#include "shell.h"
#include <unistd.h> /* Include this for gethostname */

/**
 * shell_prompt - Display the shell prompt
 */

void shell_prompt(void)
{
	char hostn[1204] = "";

	gethostname(hostn, sizeof(hostn));
	printf("%s@%s %s > ", getenv("LOGNAME"), hostn, getcwd(currentDirectory, 1024));
}
