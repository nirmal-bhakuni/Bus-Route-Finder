// Implementation of ticket booking module.

#include <stdio.h>
#include <string.h>
#include "ticket.h"

static int seats[MAX_SEATS];      /* 0 = free, 1 = booked */
static Ticket tickets[MAX_TICKETS];
static int nextTicketID = 1;

/* Initialize tickets and seat allocation */
void initTickets(void) {
    for (int i = 0; i < MAX_SEATS; i++) seats[i] = 0;
    for (int i = 0; i < MAX_TICKETS; i++) tickets[i].used = false;
    nextTicketID = 1;
}

/* Find a free seat; return seat index (0-based) or -1 */
static int findFreeSeat(void) {
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seats[i] == 0) return i;
    }
    return -1;
}

/* Find free ticket slot; return index or -1 */
static int findFreeTicketSlot(void) {
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (!tickets[i].used) return i;
    }
    return -1;
}

/* Book a ticket: assigns seat and creates ticket record */
int bookTicket(char* passengerName, char* src, char* dest) {
    if (!passengerName || !src || !dest) return -1;
    int seat = findFreeSeat();
    if (seat == -1) {
        /* no seats */
        return -1;
    }
    int slot = findFreeTicketSlot();
    if (slot == -1) return -1;

    seats[seat] = 1;
    tickets[slot].used = true;
    tickets[slot].ticketID = nextTicketID++;
    strncpy(tickets[slot].passengerName, passengerName, MAX_NAME_LEN - 1);
    tickets[slot].passengerName[MAX_NAME_LEN - 1] = '\0';
    strncpy(tickets[slot].src, src, MAX_NAME_LEN - 1);
    tickets[slot].src[MAX_NAME_LEN - 1] = '\0';
    strncpy(tickets[slot].dest, dest, MAX_NAME_LEN - 1);
    tickets[slot].dest[MAX_NAME_LEN - 1] = '\0';
    tickets[slot].seatNo = seat + 1;
    return tickets[slot].ticketID;
}

/* Cancel ticket by id and free seat */
bool cancelTicket(int ticketID) {
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (tickets[i].used && tickets[i].ticketID == ticketID) {
            int seatIndex = tickets[i].seatNo - 1;
            if (seatIndex >= 0 && seatIndex < MAX_SEATS) seats[seatIndex] = 0;
            tickets[i].used = false;
            return true;
        }
    }
    return false;
}

/* Display all booked tickets */
void displayTickets(void) {
    printf("Booked Tickets:\n");
    int count = 0;
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (tickets[i].used) {
            count++;
            printf("  TicketID: %d | Name: %s | From: %s | To: %s | Seat: %d\n",
                tickets[i].ticketID,
                tickets[i].passengerName,
                tickets[i].src,
                tickets[i].dest,
                tickets[i].seatNo);
        }
    }
    if (count == 0) printf("  (No tickets booked)\n");
}

/* Return number of free seats */
int availableSeats(void) {
    int free = 0;
    for (int i = 0; i < MAX_SEATS; i++) if (seats[i] == 0) free++;
    return free;
}