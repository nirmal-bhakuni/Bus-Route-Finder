#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "management.h"
#include "ticket.h"

#define MAX_WAITLIST 100

typedef struct {
    int ticket_id;
    char passenger_name[50];
} WaitlistEntry;

static WaitlistEntry waitlist[MAX_WAITLIST];
static int waitlist_count = 0;

int add_to_waitlist(int ticket_id, const char *passenger_name) {
    if (waitlist_count >= MAX_WAITLIST) {
        return -1; // Waitlist is full
    }
    waitlist[waitlist_count].ticket_id = ticket_id;
    strncpy(waitlist[waitlist_count].passenger_name, passenger_name, sizeof(waitlist[waitlist_count].passenger_name) - 1);
    waitlist[waitlist_count].passenger_name[sizeof(waitlist[waitlist_count].passenger_name) - 1] = '\0'; // Ensure null termination
    waitlist_count++;
    return 0; // Success
}

bool cancel_ticket_by_id(int ticket_id) {
     // Logic to cancel a ticket
    // This is a placeholder for actual cancellation logic
    printf("Ticket %d has been cancelled.\n", ticket_id);
    
    // Check if there are waitlisted passengers
    if (waitlist_count > 0) {
        // Notify the first passenger in the waitlist
        printf("Notifying %s about the available ticket %d.\n", waitlist[0].passenger_name, ticket_id);
        // Shift the waitlist
        for (int i = 1; i < waitlist_count; i++) {
            waitlist[i - 1] = waitlist[i];
        }
        waitlist_count--;
    }
    return true;
}


   
 

void print_waitlist() {
    printf("Current Waitlist:\n");
    for (int i = 0; i < waitlist_count; i++) {
        printf("Ticket ID: %d, Passenger Name: %s\n", waitlist[i].ticket_id, waitlist[i].passenger_name);
    }
}