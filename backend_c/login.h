#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char username[20];
    char password[20];
    char BckpQues[100];
    char BckpAns[20];
} Credentials;


void Setup(void);          // Create a new user account
int Login(void);           // Login to the system
void changepass(void);     // Change or view password
void changeuser(void);     // Change or view username
void newbackup(void);      // Change or view backup question/answer
void deleteacc(void);      // Delete a user account
int menu(void);            // Main menu for login module

#endif
