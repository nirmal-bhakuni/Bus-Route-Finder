// ...existing code...
#ifndef TICKET_H
#define TICKET_H

#include <stdbool.h>

#define MAX_TICKETS 100
#define MAX_SEATS 20
#define MAX_NAME_LEN 50

typedef struct {
    int ticketID;
    char passengerName[MAX_NAME_LEN];
    char src[MAX_NAME_LEN];
    char dest[MAX_NAME_LEN];
    int seatNo;     /* 1..MAX_SEATS */
    bool used;      /* whether record is in use */
} Ticket;

/* Initialize ticket system (seats and ticket store) */
void initTickets(void);

/* Book ticket; returns ticketID on success, -1 on failure */
int bookTicket(char* passengerName, char* src, char* dest);

/* Cancel ticket by ticketID; returns true if canceled */
bool cancelTicket(int ticketID);

/* Display all booked tickets */
void displayTickets(void);

/* Return number of free seats currently available */
int availableSeats(void);

#endif /* TICKET_H */
// ...existing code...