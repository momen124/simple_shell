# Shell - Simple UNIX Command Interpreter

## Description
Shell is a simple UNIX command interpreter written entirely in C that replicates the functionalities of the simple shell (sh). It includes additional functions and built-in commands.

## Installation
Clone this repository into your working directory. Compile the files using GCC with the following flags for best results:
gcc main.c -Wall -Wextra -Werror -pedantic -std=gnu89 -o main

## Usage
After compilation, you can run the resulting program in interactive or non-interactive mode.

### Interactive Mode
Run the program and wait for the prompt to appear. You can then type commands freely. Exit with the "exit" command or ctrl-D.

### Non-Interactive Mode
In non-interactive mode, echo your desired command and pipe it into the program:
echo "ls" | ./shell
The program will exit after executing your command(s).

## Included Built-Ins
The shell includes support for the following built-in commands:

| Command         | Definition                                                |
|-----------------|-----------------------------------------------------------|
| `exit [n]`      | Exit the shell, with an optional exit status, n.          |
| `env`           | Print the environment.                                    |
| `setenv [var][value]` | Set an environment variable and value. If the variable exists, the value will be updated. |
| `unsetenv [var]` | Remove an environment variable.                           |
| `cd [dir]`      | Change the directory.                                     |
| `help [built-in]` | Read documentation for a built-in command.                 |

Feel free to explore and use these built-in commands for better control and customization of your shell environment.
 
