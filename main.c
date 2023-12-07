#include "shell.h"

/**
 * main - Entry point for the shell program.
 * Return: Exit status.
 */
int main(void)
{
    if (argc > 1) {
    freopen(argv[1], "r", stdin);
}
    info_t info = {0};
    char *user_input;
    int builtin_ret;

    while (1)
    {
        display_prompt();
        user_input = read_user_input();

        if (user_input == NULL)
        {
            break; /* End of file or an error */
        }

        tokenize_command(&info, user_input);
        if (info.token_count > 0)
        {
            builtin_ret = find_builtin(&info);
            if (builtin_ret == 0)
            {
                continue; /* Built-in command executed, continue loop */
            }
            else if (builtin_ret < 0)
            {
                find_and_execute_command(&info); /* Find and execute non-built-in command */
            }
        }

        free_info(&info, 0); /* Reset info for the next iteration */
        free(user_input);
    }

    free_info(&info, 1); /* Clean up before exiting */
    return info.status;
}

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
    printf("$ ");
}

/**
 * read_user_input - Read user input from stdin.
 * Return: Pointer to the input string.
 */
char *read_user_input(void)
{
    char *input = NULL;
    size_t size = 0;
    ssize_t read_bytes = getline(&input, &size, stdin);

    if (read_bytes == -1)
    {
        free(input);
        return NULL;
    }

    /* Remove newline character if present */
    if (input[read_bytes - 1] == '\n')
    {
        input[read_bytes - 1] = '\0';
    }

    return input;
}
