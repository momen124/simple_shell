#include "shell.h"
#define INFO_INIT info_init()
/**
 * _myexit - Implementation of the exit command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myexit(info_t *info)
{
    (void)info; 
    exit(0);
}

/**
 * _myenv - Implementation of the env command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myenv(info_t *info)
{
    (void)info;
    int i;
    extern char **environ;
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
    return 0;
}

/**
 * _myhelp - Implementation of the help command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myhelp(info_t *info)
{
    (void)info;
    printf("Shell Help:\n");
    printf("Available commands:\n");
    printf("exit, env, help, history, setenv, unsetenv, cd, alias\n");
    return 0;
}

/**
 * _myhistory - Implementation of the history command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
    (void)info;
    printf("Command history feature not implemented.\n");
    return 0;
}

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
        return -1;
    }
    setenv(info->tokens[1], info->tokens[2], 1);
    return 0;
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
        return -1;
    }
    unsetenv(info->tokens[1]);
    return 0;
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
        return -1;
    }
    if (chdir(info->tokens[1]) != 0)
    {
        perror("cd");
        return -1;
    }
    return 0;
}

/**
 * _myalias - Implementation of the alias command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
    (void)info;
    printf("Alias feature not implemented.\n");
    return 0;
}
