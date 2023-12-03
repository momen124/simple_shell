 #include "shell.h"

   #define READ_BUF_SIZE 1024

   ssize_t _getline(info_t *info, char **line, size_t *n) {
       static char buffer[READ_BUF_SIZE];
       static size_t buffer_index = 0;
       static ssize_t bytes_read = 0;

       if (info->readfd == 0) {
           write(STDOUT_FILENO, "$ ", 2);
       }

       *line = NULL;
       *n = 0;

       while (1) {
           if (buffer_index == (size_t)bytes_read) {
               bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
               if (bytes_read <= 0) {
                   if (*n > 0) {
                       return (ssize_t)*n;
                   } else {
                       return -1;
                   }
               }
               buffer_index = 0;
           }

           char *new_line = realloc(*line, *n + 1);
           if (new_line == NULL) {
               free(*line);
               return -1;
           }
           *line = new_line;

           while (buffer_index < (size_t)bytes_read && buffer[buffer_index] != '\n') {
               (*line)[(*n)++] = buffer[buffer_index++];
           }

           if (buffer_index < (size_t)bytes_read && buffer[buffer_index] == '\n') {
               (*line)[(*n)++] = buffer[buffer_index++];
               return (ssize_t)*n;
           }
       }
   }
   