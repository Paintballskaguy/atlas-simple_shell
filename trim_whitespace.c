#include "shell.h"

/**
 * trim_whitespace - Trims leading and trailing whitespace from a string
 * @str: The string to be trimmed
 *
 * Return: Pointer to the trimmed string
 */

char *trim_whitespace(char *str)
{
    char *end;

    /* Trim leading space */
    while (isspace((unsigned char)*str))
        str++;

    /* All spaces */
    if (*str == 0)
        return str;

    /* Trim trailing space */
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    /* Write new null terminator character */
    end[1] = '\0';

    return str;
}
