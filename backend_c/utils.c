// Implementation of utilities.

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "utils.h"

/* Clear screen (Windows) */
void clearScreen(void) {
    /* Use system call; works on Windows (cls) */
    system("cls");
}

/* Delay in milliseconds using clock() */
void delay(int milliseconds) {
    if (milliseconds <= 0) return;
    clock_t start = clock();
    clock_t ms = (milliseconds * CLOCKS_PER_SEC) / 1000;
    while (clock() - start < ms) { /* busy wait */ }
}

/* Convert ASCII letters to lowercase */
void toLowerCase(char* str) {
    if (!str) return;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] = (char)(str[i] - 'A' + 'a');
    }
}

/* Print a simple header */
void printHeader(char* title) {
    printf("\n================ %s ================\n", title);
}