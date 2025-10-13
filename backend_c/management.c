#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "management.h"
#include "ticket.h"

#define MAX_WAITLIST 100

// structure for the waiting list
typedef struct {
    char passengerName[50];
    int desiredRouteId;
    int tempTicketId;
} WaitlistEntry;

static WaitlistEntry waitlist[MAX_WAITLIST];
static int waitlistCount = 0;


void shift_waitlist() {
    for (int i = 1; i < waitlistCount; i++) {
        waitlist[i - 1] = waitlist[i];
    }
    waitlistCount--;
}

// sdding new passesger to the waiting list
bool add_to_waitlist(const char *name, int routeId) {
    if (waitlistCount >= MAX_WAITLIST) {
        printf("Waitlist is full Cannot add new passengers.\n");
        return false;
    }
    WaitlistEntry *w = &waitlist[waitlistCount++];
    strncpy(w->passengerName, name, sizeof(w->passengerName) - 1);
    w->passengerName[sizeof(w->passengerName) - 1] = '\0';
    w->desiredRouteId = routeId;
    w->tempTicketId = 9000 + waitlistCount; 

    printf("Passenger %s added to waitlist for route %d.\n", name, routeId);
    return true;
}

// this will display current waiting list 
void display_waitinglist() {
    printf("\n=========== CURRENT WAITLIST ===========\n");
    if (waitlistCount == 0) {
        printf("No passengers are in the waiting list.\n");
        return;
    }
    for (int i = 0; i < waitlistCount; i++) {
        printf("%d. %s (Desired Route ID: %d, Temp Ticket ID: %d)\n",
               i + 1, waitlist[i].passengerName, waitlist[i].desiredRouteId,
               waitlist[i].tempTicketId);
    }
}

// cancle logic starts here 

bool cancel_ticket_by_id(int ticketId, BookingList *bookings, RouteCollection *routes) {
    if (bookings == NULL || routes == NULL) {
        printf("Error: Invalid data structures (NULL pointers) passed!\n");
        return false;
    }

    printf("\nStarting cancellation process for Ticket ID %d...\n", ticketId);

//search the booking node
    BookingNode *prev = NULL;
    BookingNode *current = bookings->head;

    while (current != NULL && current->ticketId != ticketId) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Ticket ID %d not found in booking list!\n", ticketId);
        return false;
    }

    if (!current->isActive) {
        printf("Ticket ID %d is already cancelled.\n", ticketId);
        return false;
    }

//free the seats in the rout 
    Route *r = &routes->routes[current->routeId];
    r->seats[current->seatNumber - 1] = 0;
    current->isActive = false;

    printf("Seat %d on route %s → %s has been freed.\n",
           current->seatNumber, r->starting_point, r->destination);

    if (prev == NULL)
        bookings->head = current->next;
    else
        prev->next = current->next;

    bookings->totalBookings--;

    printf("Ticket %d for %s has been successfully cancelled!\n",
           current->ticketId, current->passengerName);

    // giving seats to waiting list passenger if seats are present
    if (waitlistCount > 0) {
        WaitlistEntry nextInQueue = waitlist[0];
        printf("Assigning freed seat to waitlisted passenger: %s\n", nextInQueue.passengerName);

        Ticket newTicket;
        strcpy(newTicket.passengerName, nextInQueue.passengerName);
        newTicket.routeId = nextInQueue.desiredRouteId;

        bool booked = book_ticket(&newTicket, routes, bookings);

        if (booked)
            printf("🎟️ Waitlisted passenger %s successfully got a ticket!\n", nextInQueue.passengerName);
        else
            printf("⚠️ Could not assign seat to %s.\n", nextInQueue.passengerName);

        shift_waitlist();
    }

    free(current);
    return true;
}

// booking history display

void display_booking_history(const BookingList *bookings) {
    if (bookings == NULL || bookings->head == NULL) {
        printf("\nNo booking records found.\n");
        return;
    }

    printf("\n=========== USER BOOKING HISTORY ===========\n");
    BookingNode *temp = bookings->head;
    while (temp != NULL) {
        printf("Ticket ID: %d | Passenger: %s | Seat: %d | Route ID: %d | Status: %s\n",
               temp->ticketId, temp->passengerName, temp->seatNumber,
               temp->routeId, temp->isActive ? "Active" : "Cancelled");
        temp = temp->next;
    }
}


#ifdef TEST_MANAGEMENT
#endif
