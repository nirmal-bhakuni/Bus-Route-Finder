#ifndef TICKET_H
#define TICKET_H

#include <stdbool.h>

// Structure to represent a ticket
typedef struct {
    int ticket_id;
    char passenger_name[100];
    int route_id;
    float cost;
    bool is_cancelled;
} Ticket;

// Function prototypes
Ticket* create_ticket(int ticket_id, const char* passenger_name, int route_id, float cost);
void cancel_ticket(Ticket* ticket);
void display_ticket(const Ticket* ticket);
void free_ticket(Ticket* ticket);

#endif // TICKET_H