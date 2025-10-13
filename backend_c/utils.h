// Header for utility helper functions.

#ifndef UTILS_H
#define UTILS_H

/* Clear the console screen (Windows 'cls' expected) */
void clearScreen(void);

/* Busy-wait delay for given milliseconds (portable using time.h) */
void delay(int milliseconds);

/* Convert string to lowercase in-place (ASCII only) */
void toLowerCase(char* str);

/* Print a formatted header for sections */
void printHeader(char* title);

#endif /* UTILS_H */