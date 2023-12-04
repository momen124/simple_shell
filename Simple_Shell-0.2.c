#include "shell.h"

/* Initialize info struct */
void init_info(info_t *info)
{
  info->tokens = NULL;
  info->token_count = 0;
  info->error_message = NULL;
}

void free_info(info_t *info, int full_cleanup)
{
  if (info->tokens != NULL)
  {
    for (size_t i = 0; i < info->token_count; i++)
    {
      free(info->tokens[i]);
    }
    free(info->tokens);
  }

  if (full_cleanup && info->error_message != NULL)
  {
    free(info->error_message);
  }
}

void tokenize_command(info_t *info, char *input)
{
  const char *delimiters = " "; // Modify this for your desired delimiters
  char *token = strtok(input, delimiters);

  while (token != NULL)
  {
    info->tokens[info->token_count++] = strdup(token);
    token = strtok(NULL, delimiters);
  }
}

void execute_command(info_t *info)
{
  if (info->token_count == 0)
  {
    return; // No command to execute
  }

  // Check for built-in commands
  if (strcmp(info->tokens[0], "exit") == 0)
  {
    free_info(info, 1);
    exit(0);
  }
  else if (strcmp(info->tokens[0], "clear") == 0)
  {
    // Implement clear screen functionality
  }
  else
  {
    // Execute external program
    pid_t pid = fork();

    if (pid == 0)
    {
      execvp(info->tokens[0], info->tokens);
      perror("Error");
      exit(1);
    }
    else if (pid > 0)
    {
      // Parent process
      wait(NULL); // Wait for child to finish
    }
    else
    {
      // Error creating child process
      perror("Fork error");
      free_info(info, 1);
      exit(1);
    }
  }
}

void display_error(info_t *info)
{
  if (info->error_message != NULL)
  {
    fprintf(stderr, "Error: %s\n", info->error_message);
  }
}

void display_prompt(void)
{
  printf("$ ");
}

char *read_user_input(void)
{
  size_t size = 0;
  char *input = NULL;

  do
  {
    input = realloc(input, size + READ_BUF_SIZE);
    size += read(STDIN_FILENO, input + size, READ_BUF_SIZE - 1);
    input[size] = '\0';
  } while (!checkForEOF(input));

  if (checkForEOF(input))
  {
    free(input);
    return NULL; // Indicate EOF reached
  }

  return input;
}

int main()
{
  info_t info;
  init_info(&info);

  while (1)
  {
    display_prompt();

    char *user_input = read_user_input();

    if (user_input == NULL)
      break; // End of file reached
  }

  tokenize_command(&info, user_input);
  execute_command(&info);
  free_info(&info, 0); // Reset for next iteration

  free(user_input);
}

return 0;
}
