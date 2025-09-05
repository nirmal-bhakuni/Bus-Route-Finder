#include <stdio.h>
#include "graph.h"
#include "ticket.h"
#include "management.h"
#include "utils.h"

int main() {
    // Initialize the graph for routes
    Graph graph;
    initializeGraph(&graph);

    // Example: Add stops and routes manually
    addStop(&graph, "Stop A");
    addStop(&graph, "Stop B");
    addRoute(&graph, 0, 1, 50, 30);

    // Display available routes
    displayGraph(&graph);

    // Example: Ticket booking and cancellation (implement these if needed)
    // Ticket ticket;
    // if (book_ticket(&ticket, &graph)) {
    //     printf("Ticket booked successfully!\n");
    //     if (cancel_ticket(&ticket)) {
    //         printf("Ticket cancelled successfully!\n");
    //     }
    // }

    system("pause");
    return 0;
}