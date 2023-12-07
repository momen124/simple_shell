#include "shell.h"



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
    free_list(&info->env);
  }
  if (info->history) {
    free_list(&info->history);
  }
  if (info->alias) {
    free_list(&info->alias);
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
    return NULL;
  }
  memcpy(new_str, s, size);
  return new_str;
}
