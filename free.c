#include "shell.h"

void free_commands(operator_command_struct *commands) {
  int i;
  if (commands == NULL) return;


  for (i = 0; i < commands->count; i++) {
    free(commands->command_list[i]);
  }
  free(commands->operators);
  free(commands);
}

void free_token_info(info_t *info) {
    
  if (info == NULL) return;

  if (info->token_count > 0) {
    size_t i;
    for ( i = 0; i < info->token_count; i++) {
      free(info->tokens[i]);
    }
    free(info->tokens);
  }
  /* Free any other dynamically allocated memory used by info*/
}