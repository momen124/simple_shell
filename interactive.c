#include "shell.h"

int main()
{
    info_t info = INFO_INIT;
    char *user_input;
    int builtin_ret;

    while (1)
    {
        display_prompt();
        user_input = read_user_input();

        if (user_input == NULL)
        {
            break; // End of file or an error
        }

        tokenize_command(&info, user_input);
        if (info.token_count > 0)
        {
            builtin_ret = find_builtin(&info);
            if (builtin_ret == 0)
            {
                continue; // Built-in command executed, continue loop
            }
            else if (builtin_ret < 0)
            {
                find_and_execute_command(&info); // Find and execute non-built-in command
            }
        }

        free_info(&info, 0); // Reset info for next iteration
        free(user_input);
    }

    free_info(&info, 1); // Clean up before exiting
    return info.status;
}

void display_prompt()
{
    printf("$ ");
}

char *read_user_input()
{
    char *input = NULL;
    size_t size = 0;
    getline(&input, &size, stdin);
    return input;
}

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

    for (int i = 0; builtins[i].type; i++)
    {
        if (strcmp(info->tokens[0], builtins[i].type) == 0)
        {
            return builtins[i].func(info);
        }
    }
    return -1;
}

void find_and_execute_command(info_t *info)
{
    char *path = _getenv(info, "PATH");
    char *full_path = find_path(info, path, info->tokens[0]);

    if (full_path)
    {
        info->path = full_path;
        execute_command(info);
    }
    else
    {
        fprintf(stderr, "Command not found: %s\n", info->tokens[0]);
    }
}

void execute_command(info_t *info)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        if (execve(info->path, info->tokens, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
    }
    else
    {
        // Parent process
        waitpid(pid, &(info->status), 0);
    }
}
