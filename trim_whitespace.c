#include "shell.h"

/**
 * trim_whitespace - Trims leading and trailing whitespace from a string
 * @str: The string to be trimmed
 *
 * Return: Pointer to the trimmed string
 */

char *trim_whitespace(char *str)
{
	char *end; /* Pointer to the end of the string */

	/* Trim leading space */
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f' || *str == '\v')
		str++; /* Move the pointer forward until a non-whitespace character is found */

	/* All spaces */
	if (*str == 0)
		return str; /* If the string is all spaces, return it as is */

	/* Trim trailing space */
	end = str + strlen(str) - 1; /* Set end pointer to the last character of the string */
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r' || *end == '\f' || *end == '\v'))
		end--; /* Move the end pointer backward until a non-whitespace character is found */

	/* Write new null terminator character */
	end[1] = '\0'; /* Place a null terminator at the new end of the string */

	return str; /* Return the trimmed string */
}
