#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ticket.h"

#define MAX_TICKETS 100

typedef struct {
    int ticket_id;
    char passenger_name[50];
    int route_id;
    int cost;
} Ticket;

static Ticket tickets[MAX_TICKETS];
static int ticket_count = 0;

int book_ticket(const char *passenger_name, int route_id, int cost) {
    if (ticket_count >= MAX_TICKETS) {
        return -1; // Ticket booking limit reached
    }
    
    tickets[ticket_count].ticket_id = ticket_count + 1; // Simple ID assignment
    strncpy(tickets[ticket_count].passenger_name, passenger_name, sizeof(tickets[ticket_count].passenger_name) - 1);
    tickets[ticket_count].route_id = route_id;
    tickets[ticket_count].cost = cost;
    ticket_count++;
    
    return tickets[ticket_count - 1].ticket_id; // Return the booked ticket ID
}

int cancel_ticket(int ticket_id) {
    if (ticket_id <= 0 || ticket_id > ticket_count) {
        return -1; // Invalid ticket ID
    }
    
    for (int i = ticket_id - 1; i < ticket_count - 1; i++) {
        tickets[i] = tickets[i + 1]; // Shift tickets down
    }
    ticket_count--;
    
    return 0; // Success
}

void list_tickets() {
    printf("Booked Tickets:\n");
    for (int i = 0; i < ticket_count; i++) {
        printf("Ticket ID: %d, Passenger: %s, Route ID: %d, Cost: %d\n",
               tickets[i].ticket_id, tickets[i].passenger_name, tickets[i].route_id, tickets[i].cost);
    }
}