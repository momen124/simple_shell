#include "shell.h"
ssize_t _getline(char **line, size_t *n, info_t *info __attribute__((unused))) {

    size_t pos = 0;
    char *new_line = NULL;
    size_t size = 0;
    int bytesRead = 0;

    if (*line == NULL) {
        *n = READ_BUF_SIZE;
        *line = malloc(*n);
    }

    while ((bytesRead = read(STDIN_FILENO, (*line) + pos, (*n) - pos)) > 0) {
        pos += bytesRead;
        if ((*line)[pos - 1] == '\n') {
            break;
        }
        if (pos + 1 >= *n) {
            
            new_line = realloc(*line, *n * 2);
            if (!new_line) {
                free(*line);
                *line = NULL;
                return -1;
            }
            *n = *n * 2;
            *line = new_line;
        }
    }

    if (bytesRead == -1) {
        if (pos == 0) {
            return -1;
        }
    }

    (*line)[pos] = '\0';
    return pos;
}
