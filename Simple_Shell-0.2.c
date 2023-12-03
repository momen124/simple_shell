#include "shell.h"


void free_info(info_t *info, int full_cleanup) {
    for (int i = 0; i < info->token_count; i++) {
        free(info->tokens[i]);
    }
    info->token_count = 0;

    if (full_cleanup && info->error_message) {
        free(info->error_message);
    }
}

void tokenize_command(info_t *info, char *input) {
    int token_index = 0;
    char *token;

    token = strtok(input, TOKEN_DELIMITERS);
    while (token != NULL) {
        info->tokens[token_index] = strdup(token);
        token_index++;

        if (token_index >= MAX_TOKENS) {
            break;
        }

        token = strtok(NULL, TOKEN_DELIMITERS);
    }
    info->token_count = token_index;
}

void execute_command(info_t *info) {
    if (info->token_count == 0) {
        return; // No command to execute
    }

    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(info->tokens[0], info->tokens) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void display_error(info_t *info) {
    if (info->error_message != NULL) {
        fprintf(stderr, "Error: %s\n", info->error_message);
    }
}

int main(void) {
    info_t info = INFO_INIT;
    char *user_input;

    while (1) {
        display_prompt();
        user_input = read_user_input();

        if (!user_input) {
            break;
        }

        tokenize_command(&info, user_input);
        execute_command(&info);

        free_info(&info, 0);
        free(user_input);
    }

    free_info(&info, 1);
    return 0;
}
