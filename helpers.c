#include "helpers.h"
#include <stdlib.h>
#include <string.h>

void free_info(info_t *info, int full)
{
    // Free the tokens
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

    // If full cleanup is requested, free additional resources
    if (full)
    {
        // Free any other dynamically allocated fields in info_t
        // For example, if info->path is dynamically allocated:
        // free(info->path);
        // info->path = NULL;
    }
}

char *strdup(const char *s)
{
    if (s == NULL)
    {
        return NULL;
    }
    size_t size = strlen(s) + 1;
    char *new_str = malloc(size);
    if (new_str == NULL)
    {
        return NULL;
    }
    memcpy(new_str, s, size);
    return new_str;
}
