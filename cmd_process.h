#ifndef CMD_PROCESS_H
#define CMD_PROCESS_H

#include "shell.h"

void tokenize_command(info_t *info, char *input);
int find_builtin(info_t *info);

#endif
