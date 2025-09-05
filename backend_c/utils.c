#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>      // <-- Add this line
#include "utils.h"
#include "graph.h"      // <-- Add this line

// Function to validate if a string is a valid integer
int is_valid_integer(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// Function to read routes data from a file
int read_routes_data(const char *filename, Route *routes, int max_routes) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1; // File could not be opened
    }

    int count = 0;
    while (count < max_routes && fscanf(file, "%d %d %d %d", 
           &routes[count].start, &routes[count].end, &routes[count].cost, 
           &routes[count].time) == 4) {
        count++;
    }

    fclose(file);
    return count; // Return the number of routes read
}

// Function to write routes data to a file
int write_routes_data(const char *filename, Route *routes, int count) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        return -1; // File could not be opened
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %d %d %d\n", routes[i].start, routes[i].end, 
                routes[i].cost, routes[i].time);
    }

    fclose(file);
    return 0; // Success
}

// Utility function to trim whitespace from a string
char* trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Null terminate after the last non-space character
    *(end + 1) = '\0';

    return str;
}

// Add utility function implementations here if needed