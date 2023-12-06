#include "shell.h"
/**
 * tokenize_command - Tokenize the input command string.
 * @info: Pointer to the info_t structure.
 * @input: Input command string.
 */
void tokenize_command(info_t *info, char *input)
{
    char *token;
    char **tokens = malloc(READ_BUF_SIZE * sizeof(char *));
    size_t token_count = 0;

    token = strtok(input, " \t\r\n\a");
    while (token != NULL)
    {
        tokens[token_count++] = strdup(token);
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[token_count] = NULL;

    info->tokens = tokens;
    info->token_count = token_count;
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
    int i;

    for (i = 0; builtins[i].type; i++)
    {
        if (strcmp(info->tokens[0], builtins[i].type) == 0)
        {
            return builtins[i].func(info);
        }
    }
    return -1;
}
