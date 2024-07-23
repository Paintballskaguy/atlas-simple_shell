#include <stdio.h>

/**
 * main - prints all arguments without using ac.
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    int i = 0;
    (void)ac;  /* Cast ac to void to avoid unused parameter warning */
    while (av[i] != NULL) {
        printf("%s\n", av[i]);
        i++;
    }
    return (0);
}

