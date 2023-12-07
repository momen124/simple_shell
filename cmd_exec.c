#include "shell.h"

/**
 * find_path - Find the full path of the command.
 * @info: Pointer to the info_t structure. (Unused)
 * @path: The PATH environment variable. (Unused)
 * @command: The command to find.
 * Return: The full path of the command.
 */
char *find_path(info_t *info, char *path, char *command)
{
    (void)info;

    char *token;
    char *full_path;
    struct stat st;

    token = strtok(path, ":");
    while (token != NULL) {
        full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path) {
            return NULL;
        }

        sprintf(full_path, "%s/%s", token, command);

        if (stat(full_path, &st) == 0) {
            return full_path;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    fprintf(stderr, "Command not found in PATH: %s\n", command);
    return NULL;
}
