#include "shell.h"

operator_command_struct *parse_operators(char *input) {
operator_command_struct *result;
char *token;

result = malloc(sizeof(operator_command_struct));
if (!result) {
perror("malloc");
exit(EXIT_FAILURE);
}

result->command_list = malloc(10 * sizeof(char *));
result->operators = malloc(9 * sizeof(char *));
result->count = 0;

token = strtok(input, " ");
while (token != NULL) {
if (strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) {
result->operators[result->count - 1] = strdup(token);
} else {
result->command_list[result->count] = strdup(token);
result->count++;
}
token = strtok(NULL, " ");
}

return result;
}

void free_operator_commands(operator_command_struct *commands) {
int i;

if (!commands) return;

for (i = 0; i < commands->count; i++) {
free(commands->command_list[i]);
}
for (i = 0; i < commands->count - 1; i++) {
free(commands->operators[i]);
}
free(commands->command_list);
free(commands->operators);
free(commands);
}

char *find_command_in_PATH(const char *command) {
char *path = getenv("PATH");
char *path_dup = strdup(path);
char *token = strtok(path_dup, ":");
struct stat st;

while (token != NULL) {
char *full_path = malloc(strlen(token) + strlen(command) + 2); /* +2 for '/' and '\0' */
sprintf(full_path, "%s/%s", token, command);

if (stat(full_path, &st) == 0) {
free(path_dup);
return full_path;  /* Found executable command */
}

free(full_path);
token = strtok(NULL, ":");
}

free(path_dup);
return NULL; /* Command not found */
}

int is_executable(const char *path) {
struct stat st;
if (stat(path, &st) == 0) {
return (st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH);
}
return 0;
}