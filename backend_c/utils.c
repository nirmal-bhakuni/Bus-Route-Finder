// Implementation of utilities.

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "utils.h"

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

/* Clear screen (Windows) */
void clearScreen(void) {
    /* Use system call; works on Windows (cls) and Unix (clear) */
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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

/* Try to create a directory, ignore errors if exists */
void ensureDataDir(void) {
    /* Try "data" first */
    MKDIR("data");
    /* Also try "../data" to be safe when running from backend_c working dir */
    MKDIR("../data");
}

/* Open data file inside data folder, trying two possible relative paths.
   This helps whether program is run from project root or from backend_c directory. */
FILE* openDataFile(const char* filename, const char* mode) {
    if (!filename || !mode) return NULL;
    char path[512];

    /* Ensure directories exist (no harm if already exist) */
    ensureDataDir();

    /* Try data/<filename> */
#ifdef _WIN32
    _snprintf(path, sizeof(path), "data\\%s", filename);
#else
    snprintf(path, sizeof(path), "data/%s", filename);
#endif
    FILE* f = fopen(path, mode);
    if (f) return f;

    /* Try ../data/<filename> */
#ifdef _WIN32
    _snprintf(path, sizeof(path), "..\\data\\%s", filename);
#else
    snprintf(path, sizeof(path), "../data/%s", filename);
#endif
    f = fopen(path, mode);
    return f; /* may be NULL */
}