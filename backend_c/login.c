// Implementation of simple login and registration.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"

/* Helper: check if username already exists (ignores password) */
static bool userExists(const char* username) {
    FILE* f = fopen(USERS_FILE, "r");
    if (!f) return false; /* no file -> no user yet */
    char line[256];
    bool found = false;
    while (fgets(line, sizeof(line), f)) {
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';
        char *sep = strchr(line, ':');
        if (!sep) continue;
        *sep = '\0';
        if (strcmp(line, username) == 0) {
            found = true;
            break;
        }
    }
    fclose(f);
    return found;
}

/* Register a user by appending username:password to USERS_FILE */
bool registerUser(char* username, char* password) {
    if (!username || !password) return false;
    /* prevent very long names */
    if (strlen(username) == 0 || strlen(password) == 0) return false;
    /* check if username already exists */
    if (userExists(username)) return false;
    FILE* f = fopen(USERS_FILE, "a");
    if (!f) return false;
    fprintf(f, "%s:%s\n", username, password);
    fclose(f);
    return true;
}

/* Check username/password pair */
bool loginUser(char* username, char* password) {
    return verifyCredentials(username, password);
}

/* Verify credentials by scanning users file */
bool verifyCredentials(char* username, char* password) {
    FILE* f = fopen(USERS_FILE, "r");
    if (!f) return false;
    char line[256];
    bool found = false;
    while (fgets(line, sizeof(line), f)) {
        /* trim newline */
        char *nl = strchr(line, '\n');
        if (nl) *nl = '\0';
        char *sep = strchr(line, ':');
        if (!sep) continue;
        *sep = '\0';
        char *fileUser = line;
        char *filePass = sep + 1;
        if (strcmp(fileUser, username) == 0 && strcmp(filePass, password) == 0) {
            found = true;
            break;
        }
    }
    fclose(f);
    return found;
}