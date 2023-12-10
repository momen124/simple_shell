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
