#include "shell.h"

/**
 * main - Entry point for the shell program.
 * Return: Exit status.
 */
int main(int argc, char *argv[]) {
int main(int argc, char *argv[]) {
    info_t info = {0};
    char *user_input;
    operator_command_struct *commands;

    if (argc > 1) {
        freopen(argv[1], "r", stdin);
    }

    while (1) {
        if (isatty(STDIN_FILENO)) {
            display_prompt();
        }

        user_input = read_user_input();

        if (checkForEOF(user_input)) {
            free(user_input);
            continue;
        }

        if (user_input[0] == '\0') {
            free(user_input);
            break;
        }

        commands = parse_operators(user_input);
        if (!commands) {
            free(user_input);
            continue;
        }

        for (int i = 0; i < commands->count; i++) {
            tokenize_command(&info, commands->command_list[i]);
            if (info.token_count > 0) {
                int builtin_ret = find_builtin(&info);
                if (builtin_ret != 0) {
                    find_and_execute_command(&info);
                }
            }

            free_info_tokens(&info);  
        }

        free_operator_commands(commands);
        free(user_input);
    }

    free_info_tokens(&info);  
    free_info(&info, 1);      

    return info.status;
}

void display_prompt(void) {
    printf("$ ");
}

char *read_user_input(void) {
    char *input = NULL;
    size_t size = 0;
    ssize_t read_bytes;

    if (feof(stdin)) {
        return NULL;
    }

    read_bytes = getline(&input, &size, stdin);
    if (read_bytes == -1) {
        free(input);
        return NULL;
    }

    if (input[read_bytes - 1] == '\n') {
        input[read_bytes - 1] = '\0';
    }

    return input;
}
