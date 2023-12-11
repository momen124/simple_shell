#include "shell.h"

/**
* new_alias - Creates a new alias node.
* @name: The name of the alias.
* @value: The value of the alias.
* Return: A pointer to the new alias node.
*/
alias_t *new_alias(char *name, char *value)
{
alias_t *new = malloc(sizeof(alias_t));
if (!new)
{
perror("malloc");
exit(EXIT_FAILURE);
}
new->name = strdup(name);
new->value = strdup(value);
new->next = (NULL);
return (new);
}

/**
* add_alias - Adds a new alias to the list of aliases.
* If an alias with the same name already exists, its value is updated.
* @info: Pointer to the info_t structure.
* @name: The name of the alias.
* @value: The value of the alias.
*/
void add_alias(info_t *info, char *name, char *value)
{
alias_t *new, *current;
new = new_alias(name, value);
current = info->alias_head;

while (current)
{
if (strcmp(current->name, name) == 0)
{
free(current->value);
current->value = strdup(value);
free(new);
return;
}
current = current->next;
}

new->next = info->alias_head;
info->alias_head = new;
}

/**
* print_aliases - Prints all aliases in the format name='value'.
* @info: Pointer to the info_t structure.
*/
void print_aliases(info_t *info)
{
alias_t *current = info->alias_head;

while (current)
{
printf("%s='%s'\n", current->name, current->value);
current = current->next;
}
}

/**
* _myalias - Implementation of the alias command.
* If called with no arguments, prints all aliases.
* If called with a name, prints the value of that alias.
* If called with a name and a value, sets the value of that alias.
* @info: Pointer to the info_t structure.
* Return: Always returns 0.
*/
int _myalias(info_t *info)
{
if (info->token_count == 1)
{
print_aliases(info);
}
else
{
size_t i;
for (i = 1; i < info->token_count; i++)
{
char *name = strtok(info->tokens[i], "=");
char *value = strtok(NULL, "=");

if (value == NULL)
{
alias_t *current = info->alias_head;
while (current)
{
if (strcmp(current->name, name) == 0)
{
printf("%s='%s'\n", current->name, current->value);
break;
}
current = current->next;
}
}
else
{
add_alias(info, name, value);
}
}
}

return (0);
}
