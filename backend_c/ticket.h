#ifndef TICKET_H
#define TICKET_H

#include "graph.h"
#include <stdbool.h>

// Structure to represent a ticket
typedef struct {
    int id;
    int routeId;
    char passengerName[50];
    bool isActive;
} Ticket;

// Function prototypes
bool book_ticket(Ticket* ticket, const Graph* graph);
bool cancel_ticket(Ticket* ticket);

#endif // TICKET_H