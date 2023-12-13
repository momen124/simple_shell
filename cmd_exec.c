#include "shell.h"
char *find_path(info_t *info, char *path, char *command);

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
if (pid == 0) {
/* Child process */
signal(SIGINT, SIG_DFL);
signal(SIGTSTP, SIG_DFL);

if (execve(info->path, info->tokens, environ) == -1) {
perror("execve");
exit(EXIT_FAILURE);
}
} else if (pid < 0) {
perror("fork");
} else {
waitpid(pid, &(info->status), 0);
}
}

/**
 * find_path - Find the full path of the command.
 * @info: Pointer to the info_t structure. (Unused)
 * @path: The PATH environment variable.
 * @command: The command to find.
 * Return: The full path of the command or NULL if not found.
 */
char *find_path(info_t *info, char *path, char *command) {
struct stat st;
char *token;
char *full_path;
char copied_path[PATH_MAX + 1];

/* Mark info parameter as unused */
(void)info;

/* Check if the command is an absolute path or starts with './' */
if (command[0] == '/' || (command[0] == '.' && command[1] == '/')) {
if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR)) {
/* Command is an absolute path and executable */
return strdup(command);
}
}

/* Check if PATH environment variable is set */
if (!path) {
perror("Error: PATH environment variable not set");
return NULL;
}

/* Copy the PATH to avoid modifying the original environment variable */
strcpy(copied_path, path);

/* Iterate through each path in the PATH variable */
token = strtok(copied_path, ":");
while (token != NULL) {
full_path = malloc(strlen(token) + strlen(command) + 2);
if (!full_path) {
perror("malloc");
return NULL;
}

/* Construct the full path */
sprintf(full_path, "%s/%s", token, command);

/* Check if the command exists at this path */
if (stat(full_path, &st) == 0) {
return full_path;
}

/* Clean up and move to the next token */
free(full_path);
token = strtok(NULL, ":");
}

perror("Command not found in PATH");
return NULL;
}