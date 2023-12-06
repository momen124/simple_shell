#ifndef BUILTIN_CMDS_H
#define BUILTIN_CMDS_H

#include "shell.h"

int _myexit(info_t *info);
int _myenv(info_t *info);
int _myhelp(info_t *info);
int _myhistory(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int _mycd(info_t *info);
int _myalias(info_t *info);

#endif
