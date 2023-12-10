#include "shell.h"

/**
 * tokenize_command - Tokenize the input command string.
 * @info: Pointer to the info_t structure.
 * @input: Input command string.
 */
void tokenize_command(info_t *info, char *input)
{
size_t i;
char *token;
char **tokens = malloc(READ_BUF_SIZE * sizeof(char *));
size_t token_count = 0;

if (!tokens)
{
perror("malloc");
exit(EXIT_FAILURE);
}

token = strtok(input, " \t\r\n\a");
while (token != NULL)
{
tokens[token_count] = strdup(token);
if (!tokens[token_count])
{
perror("strdup");
for (i = 0; i < token_count; i++)
{
free(tokens[i]);
tokens[i] = NULL;
}
free(tokens);
exit(EXIT_FAILURE);
}
token_count++;
token = strtok(NULL, " \t\r\n\a");
}
tokens[token_count] = NULL;

info->tokens = tokens;
info->token_count = token_count;
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
