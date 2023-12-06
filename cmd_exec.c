#include "cmd_exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void find_and_execute_command(info_t *info) {
    char *path = getenv("PATH");
    char *full_path = find_path(info, path, info->tokens[0]);

    if (full_path) {
        info->path = full_path;
        execute_command(info);
    } else {
        fprintf(stderr, "Command not found: %s\n", info->tokens[0]);
    }
}

void execute_command(info_t *info) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(info->path, info->tokens, environ) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error forking
        perror("fork");
    } else {
        // Parent process
        waitpid(pid, &(info->status), 0);
    }
}

char *find_path(info_t *info, const char *path, const char *command) {
    // This function should search for the command in the directories
    // specified by the PATH environment variable and return the full path
    // if found. The implementation will depend on your specific requirements.

    // Placeholder implementation:
    char *full_path = malloc(strlen(command) + 1);
    strcpy(full_path, command);
    return full_path;
}
