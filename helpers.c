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
	/* Free path if it exists */
	if (info->path)
	{
		free(info->path);
		info->path = NULL; /* Nullify pointer after freeing */
	}

	/* Free environment list */
	/* Assuming free_list is a function that frees a linked list */
	if (info->env)
	{
		free_list(&(info->env));
		info->env = NULL; /* Nullify pointer after freeing */
	}

	/* Free history list */
	if (info->history)
	{
		free_list(&(info->history));
		info->history = NULL; /* Nullify pointer after freeing */
	}

	/* Free alias list */
	if (info->alias)
	{
		free_list(&(info->alias));
		info->alias = NULL; /* Nullify pointer after freeing */
	}

	/* The full flag indicates whether to free all fields of info */
	if (full)
	{
		free(info->cmd_buf);
		info->cmd_buf = NULL;

		free(info->error_message);
		info->error_message = NULL;
	}
}

char *_strdup(const char *s)
{
	int len = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--s;
	return (ret);
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
				replace_len = _strlen(buffer);
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
					replace_len = _strlen(var_value);
					memmove(input + i, var_value, replace_len);
					memset(input + i + replace_len, '\0', _strlen(input) - i - replace_len);
					i += replace_len - 1;
				}
			}
		}
		i++;
	}
}
