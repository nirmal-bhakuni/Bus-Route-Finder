// Header for utility helper functions.

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

/* Clear the console screen (Windows 'cls' expected) */
void clearScreen(void);

/* Busy-wait delay for given milliseconds (portable using time.h) */
void delay(int milliseconds);

/* Convert string to lowercase in-place (ASCII only) */
void toLowerCase(char* str);

/* Print a formatted header for sections */
void printHeader(char* title);

/* Ensure the data directory exists (tries "data" and "../data") */
void ensureDataDir(void);

/* Open a file inside the data folder. Tries "data/<filename>" then "../data/<filename>".
   Returns FILE* or NULL on failure. */
FILE* openDataFile(const char* filename, const char* mode);

#endif /* UTILS_H */