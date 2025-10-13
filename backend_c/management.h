// Header for ticket management (waiting list) module.

#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#define MAX_WAITLIST 50
#define MAX_NAME_LEN 50

/* Add a person to waiting list */
void addToWaitingList(char* name, char* src, char* dest);

/* Try to process waiting list and allocate seats if available */
void processWaitingList(void);

/* Display current waiting list */
void displayWaitingList(void);

#endif /* MANAGEMENT_H */