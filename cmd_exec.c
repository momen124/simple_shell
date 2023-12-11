#include "shell.h"
char *find_path(info_t *info, char *path, char *command);

/**
 * find_and_execute_command - Find and execute the command specified in info.
 * @info: Pointer to the info_t structure.
 */
void find_and_execute_command(info_t *info)
{
char *command_path;

if (strchr(info->tokens[0], '/') != NULL)
{
command_path = strdup(info->tokens[0]);
}
else
{
command_path = find_command_in_PATH(info->tokens[0]);
}

if (command_path != NULL && is_executable(command_path))
{
execute_command(info, command_path);
free(command_path);
}
else
{
fprintf(stderr, "Command not found: %s\n", info->tokens[0]);
free(command_path);
}
}
/**
 * execute_command - Execute the command specified in info.
 * @info: Pointer to the info_t structure.
 */
void execute_command(info_t *info, const char *command_path)
{
pid_t pid;
int status;

pid = fork();
if (pid == 0)
{
if (execve(command_path, info->argv, environ) == -1)
{
perror("execve");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("fork");
}
else
{
waitpid(pid, &status, 0);
}
}

/**
 * find_path - Find the full path of the command.
 * @info: Pointer to the info_t structure. (Unused)
 * @path: The PATH environment variable. (Unused)
 * @command: The command to find.
 * Return: The full path of the command.
 */
char *find_path(info_t *info, char *path, char *command)
{
char *token;
char *full_path;
struct stat st;
char copied_path[PATH_MAX + 1];
(void)info;
if (!path)
{
perror("Error: PATH environment variable not set");
return (NULL);
}

strcpy(copied_path, path);

token = strtok(copied_path, ":");
while (token != NULL)
{
full_path = malloc(strlen(token) + strlen(command) + 2);
if (!full_path)
{
perror("malloc");
return (NULL);
}

sprintf(full_path, "%s/%s", token, command);

if (stat(full_path, &st) == 0)
{
return (full_path);
}

free(full_path);
token = strtok(NULL, ":");
}

perror("Command not found in PATH");
return (NULL);
}
