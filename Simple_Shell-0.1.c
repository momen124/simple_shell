 #include "shell.h"

   void displayPrompt(void) {
       printf("$ ");
   }

   char *readUserInput(void) {
       size_t size = 0;
       char *input = NULL;
       _getline(NULL, &input, &size);
       return input;
   }

   int checkForEOF(char *input) {
       if (input && input[0] == EOF) {
           return 1;
       }
       return 0;
   }

   void executeCommand(char *input) {
       pid_t pid = fork();

       if (pid == 0) {
           char *argv[] = {"sh", "-c", input, NULL};
           if (execv("/bin/sh", argv) == -1) {
               perror("Error");
           }
           exit(EXIT_FAILURE);
       } else if (pid < 0) {
           perror("Error");
       } else {
           int status;
           waitpid(pid, &status, 0);
       }
   }

   void mainLoop(void) {
       while (1) {
           displayPrompt();
           char *input = readUserInput();

           if (checkForEOF(input)) {
               free(input);
               break;
           }

           executeCommand(input);
           free(input);
       }
   }

   int main() {
       mainLoop();
       return 0;
   }
   