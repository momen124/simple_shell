#include "shell.h"
#define MAX_VAR_NAME_LENGTH 256 

void free_list(list_t **head) {
  while (*head) {
    list_t *temp = *head;
    *head = (*head)->next;
    free(temp->str);
    free(temp);
  }
}

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

char *find_path(info_t *info, char *path, char *command) {
  char *token;
  char *full_path;
  struct stat st;
  char copied_path[PATH_MAX + 1]; 

  (void)info;

  if (!path) {
    perror("Error: PATH environment variable not set");
    return NULL;
  }

  strcpy(copied_path, path);

  token = strtok(copied_path, ":");
  while (token != NULL) {
    full_path = malloc(strlen(token) + strlen(command) + 2);
    if (!full_path) {
      perror("malloc");
      return NULL;
    }

    sprintf(full_path, "%s/%s", token, command);

    if (stat(full_path, &st) == 0) {
      return full_path;
    }

    free(full_path);
    token = strtok(NULL, ":");
  }

  if (full_path) {
    free(full_path);
  }

  perror("Command not found in PATH");
  return NULL;
}

void preprocess_command(info_t *info, char *input) {
  /* Use standard C comments */
  /* Declare isalnum function */
  int isalnum(int);

  /* Move declarations to the beginning of the function */
  int i = 0;
  char buffer[10];
  int replace_len = 0;
  int j = 0;

  /* Move declarations to the beginning */
  char var_name[MAX_VAR_NAME_LENGTH];
  char *var_value; 

  while (input[i] != '\0') {
    if (input[i] == '$') {
      /* Check for special variables like $? and $$ */
      if (input[i + 1] == '?' || input[i + 1] == '$') {
        if (input[i + 1] == '?') {
          sprintf(buffer, "%d", info->status);
        } else {
          sprintf(buffer, "%d", getpid());
        }
        replace_len = strlen(buffer);
        memmove(input + i, buffer, replace_len);
        memset(input + i + replace_len, '\0', strlen(input) - i - replace_len);
        i += replace_len - 1;
      } else {
        /* Handle environment variables */
        j = i + 2;
        while (isalnum(input[j]) || input[j] == '_') {
          j++;
        }
        /* Use a fixed-size array */
        strncpy(var_name, input + i + 1, j - i - 1);
        var_name[j - i - 1] = '\0';

        /* Lookup the environment variable */
        var_value = getenv(var_name);
        if (var_value != NULL) {
          /* Replace the variable with its value */
          replace_len = strlen(var_value);
          memmove(input + i, var_value, replace_len);
          memset(input + i + replace_len, '\0', strlen(input) - i - replace_len);
          i += replace_len - 1;
        }
      }
    }
    i++;
  }
}
