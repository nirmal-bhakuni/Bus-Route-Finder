#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <stdbool.h>
#include "ticket.h"

bool add_to_waitlist(const char *name, int routeId);
void display_waitlist();
bool cancel_ticket_by_id(int ticketId, BookingList *bookings, RouteCollection *routes);
void display_booking_history(const BookingList *bookings);

#endif
