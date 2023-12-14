#include "shell.h"

/**
 * checkForEOF - Check for the End-of-File (EOF) character.
 * @input: Pointer to the input string.
 * Return: 1 if EOF is encountered, 0 otherwise.
 */
int checkForEOF(char *input)
{
	if (input == NULL)
	{
		if (feof(stdin))
		{
			clearerr(stdin);
			printf("\n");
			return (1);
		}
	}
	return (0);
}

