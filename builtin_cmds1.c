#include "shell.h"

/**
 * _mysetenv - Implementation of the setenv command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _mysetenv(info_t *info)
{
if (info->token_count < 3)
{
fprintf(stderr, "setenv requires two arguments\n");
return (-1);
}
setenv(info->tokens[1], info->tokens[2], 1);
return (0);
}

/**
 * _myunsetenv - Implementation of the unsetenv command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myunsetenv(info_t *info)
{
if (info->token_count < 2)
{
fprintf(stderr, "unsetenv requires one argument\n");
return (-1);
}
unsetenv(info->tokens[1]);
return (0);
}

/**
 * _mycd - Implementation of the cd command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
if (info->token_count < 2)
{
fprintf(stderr, "cd requires a path as an argument\n");
return (-1);
}
if (chdir(info->tokens[1]) != 0)
{
perror("cd");
return (-1);
}
return (0);
}

