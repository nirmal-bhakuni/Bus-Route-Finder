// Header for simple login system.

#ifndef LOGIN_H
#define LOGIN_H

#include <stdbool.h>

#define MAX_USER_LEN 30
#define USERS_FILE "users.txt"

/* Register a new user; returns true on success */
bool registerUser(char* username, char* password);

/* Attempt to login with username/password; returns true if credentials are valid */
bool loginUser(char* username, char* password);

/* Verify credentials by checking the users file; returns true if match found */
bool verifyCredentials(char* username, char* password);

#endif /* LOGIN_H */