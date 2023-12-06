#include "shell.h"

size_t _getline(info_t *info __attribute__((unused)), char **line, size_t *n) {
  /* Existing code moved to separate block */
  static char buffer[READ_BUF_SIZE];
  static size_t buffer_index = 0;
  static ssize_t bytes_read = 0;

  do {
    if (buffer_index == 0) {
      bytes_read = read(STDIN_FILENO, buffer, READ_BUF_SIZE - 1);
      buffer[bytes_read] = '\0';
      buffer_index = 0;
    }

    *line = &buffer[buffer_index];

    while (buffer_index < (size_t)bytes_read && buffer[buffer_index] != '\n') {
      buffer_index++;
    }

    if (buffer[buffer_index] == '\n') {
      buffer_index++;
      bytes_read--; /* don't count newline */
      break;
    }

    if (bytes_read == 0 && checkForEOF(*line)) {
      return (size_t)-1; /* EOF reached */
    }

    /* Reallocate line buffer if needed */
    if (*n == 0 || *n < (size_t)bytes_read) {
      *n = bytes_read + READ_BUF_SIZE;
      *line = realloc(*line, *n);
    }

    bytes_read -= buffer_index;
    memmove(*line, buffer, bytes_read);
    buffer_index = 0;
  } while (1);

  return (size_t)bytes_read;
}

