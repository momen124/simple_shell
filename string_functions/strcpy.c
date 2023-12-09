#include "../shell.h"

/**
 * _strcpy - Copies the string pointed to by src to buffer pointed to by dest.
 *
 * @dest: Pointer to the destination buffer.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
    char *temp = dest;

    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return (temp);
}
