// Implementation of simple login and registration.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"

/* Register a user by appending username:password to USERS_FILE */
bool registerUser(char* username, char* password) {
    if (!username || !password) return false;
    /* prevent very long names */
    if (strlen(username) == 0 || strlen(password) == 0) return false;
    /* check if user already exists */
    if (verifyCredentials(username, password)) {
        /* exact match exists, treat as already registered */
        return false;
    }
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