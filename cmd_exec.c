#include "shell.h"

/**
 * find_and_execute_command - Find and execute the command specified in info.
 * @info: Pointer to the info_t structure.
 */
void find_and_execute_command(info_t *info)
{
    char *path = getenv("PATH");
    char *full_path = find_path(info, path, info->tokens[0]);

    if (full_path)
    {
        info->path = full_path;
        execute_command(info);
        free(full_path);
        info->path = NULL;
    }
    else
    {
        fprintf(stderr, "Command not found: %s\n", info->tokens[0]);
    }
}


/**
 * execute_command - Execute the command specified in info.
 * @info: Pointer to the info_t structure.
 */
void execute_command(info_t *info)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execve(info->path, info->tokens, environ) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("fork");
    }
    else
    {
        /* Parent process */
        waitpid(pid, &(info->status), 0);
    }
}

/**
 * find_path - Find the full path of the command.
 * @info: Pointer to the info_t structure. (Unused)
 * @path: The PATH environment variable.
 * @command: The command to find.
 * Return: The full path of the command or NULL if not found.
 */
char *find_path(info_t *info, char *path, char *command)
{
    struct stat st;
    char *fullpath = NULL;
    unsigned int com_length, pa_length, orig_pa_length;
    char *path_copy, *token;

    (void)info;

    /* Check if the command is an absolute path or starts with './' */
    if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
    {
        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            /* Command is an absolute path and executable */
            return strdup(command);
        }
    }

    com_length = strlen(command);
    orig_pa_length = strlen(path);

    /* Allocate memory for a copy of the PATH variable */
    path_copy = malloc(sizeof(char) * orig_pa_length + 1);
    if (path_copy == NULL)
    {
        perror("malloc");
        return (NULL);
    }

    /* Copy PATH variable to path_copy */
    strcpy(path_copy, path);

    token = strtok(path_copy, ":");
    
    /* Iterate through directories in the PATH variable */
    while (token != NULL)
    {
        pa_length = strlen(token);
        /* Allocate memory for the full path of the command */
        fullpath = malloc(sizeof(char) * (pa_length + com_length) + 2);
        if (fullpath == NULL)
        {
            perror("malloc");
            free(path_copy);
            return (NULL);
        }

        /* Construct full path by concatenating directory */
        strcpy(fullpath, token);
        fullpath[pa_length] = '/';
        strcpy(fullpath + pa_length + 1, command);
        fullpath[pa_length + com_length + 1] = '\0';

        /* Validate if fullpath executable (has execute permissions) */
        if (access(fullpath, X_OK) == 0)
        {
            break;
        }

        /* Clean up */
        free(fullpath);
        fullpath = NULL;
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return fullpath;
}