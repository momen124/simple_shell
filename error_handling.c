#include "shell.h"

/**
 * report_error - Report an error and exit the program.
 * @error_message: Error message to be printed.
 */
void report_error(const char *error_message)
{
fprintf(stderr, "Error: %s\n", error_message);
}
