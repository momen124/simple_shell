#include "shell.h"
#define MAX_VAR_NAME_LENGTH 256

void free_list(list_t **head)
{
while (*head)
{
list_t *temp = *head;
*head = (*head)->next;
free(temp->str);
free(temp);
}
}

void free_info(info_t *info, int full)
{
size_t i;
for (i = 0; i < info->token_count; i++)
{
free(info->tokens[i]);
}
free(info->tokens);
if (info->path)
{
free(info->path);
}
if (info->env)
{
free_list(&(info->env));
}
if (info->history)
{
free_list(&(info->history));
}
if (info->alias)
{
free_list(&(info->alias));
}
if (full)
{
free(info->cmd_buf);
}
if (info->error_message)
{
free(info->error_message);
}
free(info);
}

char *strdup(const char *s)
{
size_t size = strlen(s) + 1;
char *new_str = malloc(size);
if (!new_str)
{
perror("malloc");
return NULL;
}
memcpy(new_str, s, size);
return new_str;
}

void preprocess_command(info_t *info, char *input)
{
int isalnum(int);

int i = 0;
char buffer[10];
int replace_len = 0;
int j = 0;

char var_name[MAX_VAR_NAME_LENGTH];
char *var_value;

while (input[i] != '\0')
{
if (input[i] == '$')
{
if (input[i + 1] == '?' || input[i + 1] == '$')
{
if (input[i + 1] == '?')
{
sprintf(buffer, "%d", info->status);
}
else
{
sprintf(buffer, "%d", getpid());
}
replace_len = strlen(buffer);
memmove(input + i, buffer, replace_len);
memset(input + i + replace_len, '\0', strlen(input) - i - replace_len);
i += replace_len - 1;
}
else
{
j = i + 2;
while (isalnum(input[j]) || input[j] == '_')
{
j++;
}
strncpy(var_name, input + i + 1, j - i - 1);
var_name[j - i - 1] = '\0';

var_value = getenv(var_name);
if (var_value != NULL)
{
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
