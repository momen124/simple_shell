#include "shell.h"
void free_commands(operator_command_struct *commands);
void free_token_info(info_t *info);
/**
 * main - Entry point for the shell program.
 * Return: Exit status.
 */
int main(int argc, char *argv[]) {
info_t info = {0};
char *user_input;
int builtin_ret;
int last_command_status = 0;
int i;
operator_command_struct *commands;

if (argc > 1) {
freopen(argv[1], "r", stdin);
}

while (1) {
if (isatty(STDIN_FILENO)) {
display_prompt();
}

user_input = read_user_input();

/* Check for EOF */
if (checkForEOF(user_input)) {
free(user_input);
continue;
}

if (user_input[0] == '\0') {
free(user_input);
break;
}

commands = parse_operators(user_input);
if (!commands) { 
free(user_input);
continue;
}

for (i = 0; i < commands->count; i++) {
if (i > 0 && commands->operators[i - 1] != NULL && 
((strcmp(commands->operators[i - 1], "&&") == 0 && last_command_status != 0) ||
 (strcmp(commands->operators[i - 1], "||") == 0 && last_command_status == 0))) {
continue;
}
free_commands(commands);

tokenize_command(&info, commands->command_list[i]);
if (info.token_count > 0) {
builtin_ret = find_builtin(&info);
if (builtin_ret != 0) {
find_and_execute_command(&info);
}
}
free_token_info(&info);

last_command_status = info.status;
free_info(&info, 0);
}

free_operator_commands(commands);
free(user_input);
}

free_info(&info, 1);
return info.status;
}

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void) {
printf("$ ");
}

/**
 * read_user_input - Read user input from stdin.
 * Return: Pointer to the input string.
 */
char *read_user_input(void) {
static char *buffer = NULL;  /* Persistent buffer for input */
static size_t bufIndex = 0;  /* Current position in buffer */
size_t bufSize = 0;  /* Size of the buffer */
ssize_t lineSize;/* Size of the read line */
size_t commandStart; /* Starting position of the next command */
char *nextCommand;   /* Pointer to the next command */
char *command;   /* Pointer to the current command to return */

/* Allocate or reallocate buffer if necessary */
if (buffer == NULL || buffer[bufIndex] == '\0') {
free(buffer);  /* Free the previous buffer if it's fully processed */
buffer = NULL;
bufIndex = 0;
lineSize = getline(&buffer, &bufSize, stdin);

if (lineSize == -1) {
free(buffer);
return NULL;  /* Handle EOF or read error */
}

/* Replace newline character with null terminator */
if (buffer[lineSize - 1] == '\n') {
buffer[lineSize - 1] = '\0';
}
}

/* Find the next command in the buffer */
commandStart = bufIndex;
nextCommand = buffer + commandStart;
while (buffer[bufIndex] != ';' && buffer[bufIndex] != '\0') {
bufIndex++;
}

/* If a semicolon is found, process the command up to the semicolon */
if (buffer[bufIndex] == ';') {
buffer[bufIndex] = '\0'; /* Replace semicolon with null terminator */
bufIndex++;  /* Move past the null terminator */
}

/* Copy the current command to a new buffer to return */
command = strdup(nextCommand);
if (command == NULL) {
perror("strdup");
return NULL;
}
free(buffer);

return command;
}
