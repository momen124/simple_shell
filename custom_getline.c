#include "shell.h"

ssize_t _getline(char **line, size_t *n) 
{
  if (line == NULL || n == NULL)
  {
    errno = EINVAL;
    return -1;
  }

  if (*line == NULL || *n == 0)
  {
    *n = READ_BUF_SIZE;
    *line = malloc(*n);
    if (*line == NULL)
    {
      return -1;
    }
  }

  size_t pos = 0;
  size_t bytesRead = 0;
  while (1)
  {
    bytesRead = read(STDIN_FILENO, *line + pos, *n - pos - 1);
    if (bytesRead == -1)
    {
      if (errno == EINTR)
      {
        continue;
      }
      free(*line);
      return -1;
    }

    if (bytesRead == 0)
    { 
      if (pos == 0)
      {
        free(*line);
        return -1;
      }
      break;
    }

    pos += bytesRead;
    if (pos > 0 && (*line)[pos - 1] == '\n')
    {
      break;
    }

    if (pos + 1 == *n)
    {
      *n *= 2;
      char *new_line = realloc(*line, *n);
      if (new_line == NULL)
      {
        free(*line);
        return -1;
      }
      *line = new_line;
    }
  }

  (*line)[pos] = '\0';
  return (ssize_t)pos;
}