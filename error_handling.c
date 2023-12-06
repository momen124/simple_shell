#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>

void report_error(const char *error_message) {
    // Prints the error message to stderr
    fprintf(stderr, "Error: %s\n", error_message);

    // Here you can add more sophisticated error handling
    // like logging to a file, cleaning up resources, etc.

    // For now, let's just exit the program with an error status
    exit(EXIT_FAILURE);
}
