#include "shell.h"

/**
 * _puts - Prints a string, followed by a new line, to stdout.
 *
 * @str: Pointer to the string.
 */
void _puts(char *s)
{
	unsigned int len;

	len = _strlen(s);

	write(STDOUT_FILENO, s, len);
}
