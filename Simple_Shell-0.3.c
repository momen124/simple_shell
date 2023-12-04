#include "shell.h"

/* Function to display the shell prompt */
void display_prompt()
{
    printf("$ ");
}

/* Function to tokenize the user input */
char **tokenize_input(char *input)
{
    /* Tokenize the input here. This is a placeholder logic. */
    char **tokens = malloc(sizeof(char *) * 10);
    int i = 0;
    char *token = strtok(input, " ");

    while (token != NULL)
    {
        tokens[i++] = strdup(token);
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return tokens;
}

/* Function to execute the command */
void execute_command(char **args)
{
    if (execvp(args[0], args) == -1)
    {
        perror("Command execution failed");
    }
}

int main()
{
    char *input = NULL;
    size_t input_size = 0;

    while (1)
    {
        display_prompt();

        /* Read user input */
        if (getline(&input, &input_size, stdin) == -1)
        {
            printf("\n");
            break; /* Handle EOF (Ctrl+D) */
        }

        /* Tokenize input */
        char **args = tokenize_input(input);

        /* Check for EOF */
        if (args[0] == NULL)
        {
            free(input);
            break;
        }

        /* Execute command */
        pid_t pid = fork();
        if (pid == 0)
        {
            /* Child process */
            execute_command(args);
        }
        else if (pid > 0)
        {
            /* Parent process */
            wait(NULL);
        }
        else
        {
            perror("Fork failed");
        }

        /* Free memory */
        for (int i = 0; args[i] != NULL; i++)
        {
            free(args[i]);
        }
        free(args);
    }

    free(input);
    return 0;
}
