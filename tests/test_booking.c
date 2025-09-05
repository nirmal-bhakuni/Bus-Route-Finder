#include <stdio.h>
#include <assert.h>
#include "ticket.h"

void test_ticket_booking() {
    TicketList tickets;
    initialize_ticket_list(&tickets);

    // Test booking a ticket
    assert(book_ticket(&tickets, "A", "B", 10) == 0);
    assert(tickets.count == 1);
    assert(strcmp(tickets.tickets[0].from, "A") == 0);
    assert(strcmp(tickets.tickets[0].to, "B") == 0);
    assert(tickets.tickets[0].cost == 10);

    // Test booking another ticket
    assert(book_ticket(&tickets, "C", "D", 15) == 0);
    assert(tickets.count == 2);
    assert(strcmp(tickets.tickets[1].from, "C") == 0);
    assert(strcmp(tickets.tickets[1].to, "D") == 0);
    assert(tickets.tickets[1].cost == 15);

    // Test booking with invalid data
    assert(book_ticket(&tickets, "", "E", 20) == -1); // Invalid from
    assert(book_ticket(&tickets, "F", "", 20) == -1); // Invalid to
    assert(book_ticket(&tickets, "G", "H", -5) == -1); // Invalid cost

    // Clean up
    free_ticket_list(&tickets);
}

void test_ticket_cancellation() {
    TicketList tickets;
    initialize_ticket_list(&tickets);
    book_ticket(&tickets, "A", "B", 10);
    book_ticket(&tickets, "C", "D", 15);

    // Test cancellation
    assert(cancel_ticket(&tickets, 0) == 0);
    assert(tickets.count == 1);
    assert(strcmp(tickets.tickets[0].from, "C") == 0);

    // Test cancellation of non-existing ticket
    assert(cancel_ticket(&tickets, 5) == -1);

    // Clean up
    free_ticket_list(&tickets);
}

int main() {
    test_ticket_booking();
    test_ticket_cancellation();
    printf("All tests passed!\n");
    return 0;
}