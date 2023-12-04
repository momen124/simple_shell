#include "shell.h"

// Function to display the shell prompt
void display_prompt() {
    printf("$ ");
}

// Function to tokenize the user input
char **tokenize_input(char *input) {
    // Implement your tokenizer logic here
    // This is just a placeholder
    char **tokens = malloc(sizeof(char *) * 10);
    tokens[0] = "ls";
    tokens[1] = "-l";
    tokens[2] = NULL;
    return tokens;
}

// Function to execute the command
void execute_command(char **args) {
    // Implement your command execution logic here
    // This is just a placeholder
    if (execvp(args[0], args) == -1) {
        perror("Command execution failed");
    }
}

int main() {
    char *input;
    size_t input_size = 0;

    while (1) {
        display_prompt();

        // Read user input
        if (getline(&input, &input_size, stdin) == -1) {
            // Handle EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Tokenize input
        char **args = tokenize_input(input);

        // Check for EOF
        if (args[0] == NULL) {
            free(input);
            break;
        }

        // Execute command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execute_command(args);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            perror("Fork failed");
        }

        // Free memory
        free(args);
    }

    return 0;
}
