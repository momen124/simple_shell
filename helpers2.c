#include "shell.h"

operator_command_struct *parse_operators(char *input) {
operator_command_struct *result;
char *token;
int cmd_index = 0, i;

/* Allocate memory for the structure */
result = malloc(sizeof(operator_command_struct));
if (!result) {
perror("malloc");
return NULL;
}

/* Allocate memory for command list and operators */
result->command_list = malloc(10 * sizeof(char *));
result->operators = malloc(9 * sizeof(char *));
if (!result->command_list || !result->operators) {
free(result->command_list);
free(result->operators);
free(result);
return NULL;
}

/* Initialize operators array */
for (i = 0; i < 9; ++i) {
result->operators[i] = NULL;
}
result->count = 0;

/* Parse the input string */
token = strtok(input, " ");
while (token != NULL) {
if ((strcmp(token, "&&") == 0 || strcmp(token, "||") == 0) && result->count > 0) {
result->operators[cmd_index] = strdup(token);
if (!result->operators[cmd_index]) {
/* Free allocated memory in case of error */
for (i = 0; i < cmd_index; ++i) {
free(result->operators[i]);
}
for (i = 0; i < result->count; ++i) {
free(result->command_list[i]);
}
free(result->command_list);
free(result->operators);
free(result);
return NULL;
}
cmd_index++;
} else {
char *new_command = NULL;
if (cmd_index == result->count) {
new_command = strdup(token);
if (!new_command) {
/* Free allocated memory in case of error */
for (i = 0; i < result->count; ++i) {
free(result->command_list[i]);
}
for (i = 0; i < cmd_index; ++i) {
free(result->operators[i]);
}
free(result->command_list);
free(result->operators);
free(result);
return NULL;
}
result->command_list[result->count++] = new_command;
} else {
size_t new_size = strlen(result->command_list[cmd_index]) + strlen(token) + 2;
new_command = malloc(new_size);
if (!new_command) {
perror("malloc");
/* Free allocated memory in case of error */
for (i = 0; i < result->count; ++i) {
free(result->command_list[i]);
}
for (i = 0; i < cmd_index; ++i) {
free(result->operators[i]);
}
free(result->command_list);
free(result->operators);
free(result);
return NULL;
}
sprintf(new_command, "%s %s", result->command_list[cmd_index], token);
free(result->command_list[cmd_index]);
result->command_list[cmd_index] = new_command;
}
}
token = strtok(NULL, " ");
}

return result;
}

void free_operator_commands(operator_command_struct *commands) {
int i;
if (!commands) return;

/* Free each command in the command list */
for (i = 0; i < commands->count; i++) {
if (commands->command_list[i]) {
free(commands->command_list[i]);
}
}

/* Free each operator */
for (i = 0; i < commands->count - 1; i++) {
if (commands->operators[i]) {
free(commands->operators[i]);
}
}

/* Finally, free the arrays and the struct itself */
free(commands->command_list);
free(commands->operators);
free(commands);
}
