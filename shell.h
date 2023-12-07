#include "shell.h"

/**
 * Frees all dynamically allocated memory in a linked list of strings.
 *
 * @param head Pointer to the head of the linked list.
 */
void free_list(list_t **head) {
  while (*head) {
    list_t *temp = *head;
    *head = (*head)->next;
    free(temp->str);
    free(temp);
  }
}

/**
 * Frees all dynamically allocated memory associated with the info structure.
 *
 * @param info Pointer to the info structure.
 * @param full Whether to free the command buffer.
 */
void free_info(info_t *info, int full) {
  size_t i;

  for (i = 0; i < info->token_count; i++) {
    free(info->tokens[i]);
  }
  free(info->tokens);

  if (info->path) {
    free(info->path);
  }

  if (info->env) {
    free_list(&(info->env));
  }

  if (info->history) {
    free_list(&(info->history));
  }

  if (info->alias) {
    free_list(&(info->alias));
  }

  if (full) {
    free(info->cmd_buf);
  }

  if (info->error_message) {
    free(info->error_message);
  }

  free(info);
}

/**
 * Duplicates a string into newly allocated memory.
 *
 * @param s String to duplicate.
 * @return Pointer to the newly allocated string, or NULL on error.
 */
char *strdup(const char *s) {
  size_t size = strlen(s) + 1;
  char *new_str = malloc(size);

  if (!new_str) {
    perror("malloc");
    return NULL;
  }

  memcpy(new_str, s, size);
  return new_str;
}

/**
 * Finds the full path of a command using the PATH environment variable.
 *
 * @param info Pointer to the info structure.
 * @param path The PATH environment variable.
 * @param command The command name.
 * @return Pointer to the full path of the command, or NULL on error.
 */
char *find_path(info_t *info, char *path, char *command) {
  char *token;
  char *full_path;
  struct stat st;
  (void)info;

  if (!path) {
    perror("Error: PATH environment variable not set");
    return NULL;
  }

  char *copied_path = strdup(path);

  if (!copied_path) {
    return NULL;
  }

  token = strtok(copied_path, ":");

  while (token != NULL) {
    full_path = malloc(strlen(token) + strlen(command) + 2);

    if (!full_path) {
      free(copied_path);
      perror("malloc");
      return NULL;
    }

    sprintf(full_path, "%s/%s", token, command);

    if (stat(full_path, &st) == 0) {
      free(copied_path);
      return full_path;
    }

    free(full_path);
    token = strtok(NULL, ":");
  }

  free(copied_path);

  perror("Command not found in PATH");
  return NULL;
}

/**
 * Preprocesses the user input by removing comments and replacing variables.
 *
 * @param info Pointer to the info structure.
 * @param input User input string.
 */
void preprocess_command(info_t *info, char *input) {
  // Use standard C comments

  // Detect and remove comments
  char *comment_start = strchr(input, '#');

  if (comment_start != NULL) {
    *comment_start = '\0';
  }

  int i = 0;
  while (input[i] != '\0') {
    if (input[i] == '$') 
	{
      if (input[i + 1] == '?' || input[i + 1] == '$') {
        char buffer[10];

        if (input[i + 1] == '?') {
          sprintf(buffer, "%d", info->status);
        } else {
          sprintf(buffer, "%d", getpid());
        }

        int replace_len = strlen(buffer);
        memmove(input + i, buffer, replace_len);
        memset(input + i + replace_len, '\0', strlen(input) - i - replace_len);
        i += replace_len - 1;
      } else {

        int j = i + 2;

        while (isalnum(input[j]) || input[j] == '_') {
          j++;
        }

        char var_name[MAX_VAR_NAME_LENGTH];
        strncpy(var_name, input + i + 1, j - i - 1);
        var_name[j - i - 1] = '\0';

        char *var_value = getenv(var_name);

        if (var_value != NULL) 
		{
          int replace_len = strlen(var_value);
          memmove(input + i, var_value, replace_len);
          memset(input + i + replace_len, '\0', strlen(input) - i - replace_len);
          i += replace_len - 1;
        }
      }
    }
    i++;
  }
}
