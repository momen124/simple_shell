#include "builtin_cmds.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int _myexit(info_t *info)
{
    // Implement the exit command
    exit(0);
}

int _myenv(info_t *info)
{
    // Implement the env command
    // This should list all environment variables
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
    return 0;
}

int _myhelp(info_t *info)
{
    // Implement the help command
    printf("Shell Help:\n");
    printf("Available commands:\n");
    printf("exit, env, help, history, setenv, unsetenv, cd, alias\n");
    return 0;
}

int _myhistory(info_t *info)
{
    // Implement the history command
    // This would normally display the history of commands executed.
    // Placeholder for demonstration as actual history implementation will vary
    printf("Command history feature not implemented.\n");
    return 0;
}

int _mysetenv(info_t *info)
{
    // Implement the setenv command
    // This should set an environment variable
    if (info->token_count < 3)
    {
        fprintf(stderr, "setenv requires two arguments\n");
        return -1;
    }
    setenv(info->tokens[1], info->tokens[2], 1);
    return 0;
}

int _myunsetenv(info_t *info)
{
    // Implement the unsetenv command
    if (info->token_count < 2)
    {
        fprintf(stderr, "unsetenv requires one argument\n");
        return -1;
    }
    unsetenv(info->tokens[1]);
    return 0;
}

int _mycd(info_t *info)
{
    // Implement the cd command
    if (info->token_count < 2)
    {
        fprintf(stderr, "cd requires a path as argument\n");
        return -1;
    }
    if (chdir(info->tokens[1]) != 0)
    {
        perror("cd");
        return -1;
    }
    return 0;
}

int _myalias(info_t *info)
{
    // Implement the alias command
    // Placeholder for demonstration as actual alias implementation will vary
    printf("Alias feature not implemented.\n");
    return 0;
}
