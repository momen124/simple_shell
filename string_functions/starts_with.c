#include "../shell.h"

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: address of next char of haystack or null
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}