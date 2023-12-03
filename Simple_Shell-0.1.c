#include "shell.h"



void displayPrompt(void) {
    printf("$ ");
}

char *readUserInput(void) {
    // Implement reading user input (use dynamic memory allocation)
    // Return the input string
     size_t size = 0;
    return _getline(&input, &size, stdin);
}

int checkForEOF(char *input) {
    // Check for EOF (Ctrl+D)
    // Return 1 if EOF, 0 otherwise
     if (input[0] == EOF) {
        return 1;
    }
    return 0;
}

void executeCommand(char *input) {
    // Implement executing the command using fork, exec, and wait
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        char *argv[] = {"sh", "-c", input, NULL};
        if (execv("/bin/sh", argv) == -1) {
            displayError();
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        displayError();
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

void displayError(void) {
    // Display an error message
    perror("Error");
}

void mainLoop(void) {
    do {
        displayPrompt();
        char *input = readUserInput();

        if (checkForEOF(input)) {
            free(input);
            break;
        }

        executeCommand(input);
        free(input);

    } while (1);
}

int main() {
    mainLoop();

    // Clean up and end the program
    return 0;
}
