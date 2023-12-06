#include "shell.h"

/**
 * free_info - Free dynamically allocated fields in info_t.
 * @info: Pointer to the info_t structure.
 * @full: Indicator for full cleanup.
 */
void free_info(info_t *info, int full)
{
    /* Free the tokens */
    if (info->tokens != NULL)
    {
    for (size_t i = 0; i < info->token_count; i++) 
        {
            free(info->tokens[i]);
        }
        free(info->tokens);
        info->tokens = NULL;
        info->token_count = 0;
    }

    /** Free any other dynamically allocated fields in info_t
     * For example, if info->path is dynamically allocated:
     * free(info->path);
     * info->path = NULL;
     */

    /* If full cleanup is requested, free additional resources */
    if (full)
    {
        /* Add any additional cleanup steps here*/
    }
}

/**
 * strdup - Duplicates a string.
 * @s: The input string.
 * Return: A pointer to the duplicated string.
 */
char *strdup(const char *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    size_t size = strlen(s) + 1;
char *new_str = malloc(size);
if (!new_str) {
  return NULL;
}
memcpy(new_str, s, size);
return new_str;
}
