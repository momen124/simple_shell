#include "shell.h"

/**
 * tokenize_command - Tokenize the input command string.
 * @info: Pointer to the info_t structure.
 * @input: Input command string.
 */
char **tokenize_command(char *str) {
char **tokens;
char *token;
unsigned int i;
tokens = malloc(sizeof(char *) * BUFFER);
if (tokens == NULL) {
perror("malloc");
exit(EXIT_FAILURE);
}
token = strtok(str, "\n\t\r ");
i = 0;
while (token != NULL) {
tokens[i] = token;
token = strtok(NULL, "\n\t\r ");
i++;
}
tokens[i] = NULL;
return tokens;
}
/**
 * free_info_tokens - Free memory allocated for tokens in info.
 * @info: Pointer to the info_t structure.
 */
void free_info_tokens(info_t *info)
{
size_t i;

for (i = 0; i < info->token_count; i++)
{
free(info->tokens[i]);
}
free(info->tokens);
info->tokens = NULL;
info->token_count = 0;
}

/**
 * find_builtin - Find if the command is a built-in command.
 * @info: Pointer to the info_t structure.
 * Return: 0 if built-in command found, -1 otherwise.
 */
int find_builtin(info_t *info)
{
static const builtin_table builtins[] = {
{"exit", _myexit},
{"env", _myenv},
{"help", _myhelp},
{"history", _myhistory},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", _mycd},
{"alias", _myalias},
{NULL, NULL}};
size_t i;

for (i = 0; builtins[i].type; i++)
{
if (strcmp(info->tokens[0], builtins[i].type) == 0)
{
return (builtins[i].func(info));
}
}
return (-1);
}
