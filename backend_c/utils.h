#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

// Function prototypes for utility functions

// Validates the input data for routes and tickets
bool validate_input(const char *input);

// Reads data from a file and populates the necessary structures
bool read_data_from_file(const char *filename);

// Writes data to a file for persistence
bool write_data_to_file(const char *filename);

// Utility function to free allocated memory for linked lists
void free_linked_list(void *head);

// Utility function to print error messages
void print_error(const char *message);

#endif // UTILS_H