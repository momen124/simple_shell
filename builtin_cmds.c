#include "shell.h"

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
int i;

(void)info;

for (i = 0; environ[i] != NULL; i++)
{
printf("%s\n", environ[i]);
}
return (0);
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
return (0);
}

/**
 * _myhistory - Implementation of the history command.
 * @info: Pointer to the info_t structure.
 * Return: Always returns 0.
 */
int _myhistory(info_t *info)
{
int i;

(void)info;

for (i = 0; i < 10 && info->cmd_buf[i] != NULL; i++)
{
printf("%s\n", info->cmd_buf[i]);
}

return (0);
}
