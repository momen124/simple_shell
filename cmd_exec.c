#include "shell.h"

/**
 * find_and_execute_command - Find and execute the command specified in info.
 * @info: Pointer to the info_t structure.
 */
void find_and_execute_command(info_t *info)
{
    char *path = getenv("PATH");
    char *full_path = find_path(info, path, info->tokens[0]);

    if (full_path)
    {
        info->path = full_path;
        execute_command(info);
    }
    else
    {
        fprintf(stderr, "Command not found: %s\n", info->tokens[0]);
    }
}

/**
 * execute_command - Execute the command specified in info.
 * @info: Pointer to the info_t structure.
 */
void execute_command(info_t *info)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(info->path, info->tokens, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("fork");
    }
    else
    {
        /* Parent process */
        waitpid(pid, &(info->status), 0);
    }
}

/**
 * find_path - Find the full path of the command.
 * @info: Pointer to the info_t structure.
 * @path: The PATH environment variable.
 * @command: The command to find.
 * Return: The full path of the command.
 */
char *find_path(info_t *info, const char *path, const char *command) 
{
    (void)info;
    (void)path;
    char *full_path = malloc(strlen(command) + 1);
    strcpy(full_path, command);
    return full_path;
}
