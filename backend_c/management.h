#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "ticket.h"

// Function to cancel a ticket based on the ticket ID
int cancel_ticket(int ticket_id);

// Function to add a ticket to the waiting list
int add_to_waiting_list(Ticket ticket);

// Function to remove a ticket from the waiting list
int remove_from_waiting_list(int ticket_id);

// Function to display the current waiting list
void display_waiting_list();

#endif // MANAGEMENT_H