#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ticket.h"

bool book_ticket(Ticket* ticket, const Graph* graph) {
    // Dummy implementation
    if (graph->routeCount == 0) return false;
    ticket->id = 1;
    ticket->routeId = 0;
    strcpy(ticket->passengerName, "John Doe");
    ticket->isActive = true;
    return true;
}

bool cancel_ticket(Ticket* ticket) {
    if (!ticket->isActive) return false;
    ticket->isActive = false;
    return true;
}