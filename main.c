#include "shell.h"

/**
 * main - Entry point for the shell program.
 * Return: Exit status.
 */
int main(int argc, char *argv[])
{
	info_t info = {0};
	char *user_input;
	int builtin_ret;
	int last_command_status = 0;
	int i;
	operator_command_struct *commands;

	/* Set up signal handler for Ctrl+C (SIGINT) */
	signal(SIGINT, handle_sigint);

	if (argc > 1)
	{
		freopen(argv[1], "r", stdin);
	}

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			display_prompt();
		}

		user_input = read_user_input();

		/* Handle EOF (Ctrl+D) and errors from read_user_input */
		if (user_input == NULL)
		{
			if (isatty(STDIN_FILENO))
			{
				printf("\n");
			}
			break; /* Exit the loop and therefore the shell */
		}

		/* Check for empty input (just Enter key) */
		if (user_input[0] == '\0')
		{
			free(user_input);
			continue; /* Continue to the next iteration of the loop */
		}

		commands = parse_operators(user_input);
		if (!commands)
		{
			free(user_input);
			continue;
		}

		for (i = 0; i < commands->count; i++)
		{
			if (i > 0 && commands->operators[i - 1] != NULL &&
					((strcmp(commands->operators[i - 1], "&&") == 0 && last_command_status != 0) ||
					 (strcmp(commands->operators[i - 1], "||") == 0 && last_command_status == 0)))
			{
				continue;
			}

			info.tokens = tokenize_command(commands->command_list[i]);
			info.token_count = 0;
			while (info.tokens[info.token_count] != NULL)
			{
				info.token_count++;
			}

			if (info.token_count > 0)
			{
				builtin_ret = find_builtin(&info);
				if (builtin_ret != 0)
				{
					find_and_execute_command(&info);
				}
			}

			last_command_status = info.status;
			free(info.tokens);
		}

		/* Free resources */
		free_operator_commands(commands);
		free(user_input);
	}

	free_info(&info, 1);
	return (info.status);
}

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * read_user_input - Read user input from stdin.
 * Return: Pointer to the input string.
 */
char *read_user_input(void)
{
	static char *buffer = NULL;
	char *command;
	ssize_t lineSize;
	size_t bufSize = 0;

	/* Read line from stdin */
	lineSize = getline(&buffer, &bufSize, stdin);

	if (lineSize == -1)
	{
		/* Free buffer if getline fails or EOF is reached */
		free(buffer);
		buffer = NULL; /* Reset static buffer to NULL */
		return (NULL);
	}

	/* Replace newline character with null terminator */
	if (buffer[lineSize - 1] == '\n')
	{
		buffer[lineSize - 1] = '\0';
	}

	command = strdup(buffer);
	if (!command)
	{
		perror("strdup");
		/* No need to free buffer here, it will be reused or freed on next call */
		return (NULL);
	}

	if (_strchr(buffer, ';') == NULL ||
	_strchr(buffer, ';') == buffer + _strlen(buffer) - 1)
	{
		free(buffer);
		buffer = NULL;
	}

	return (command);
}
