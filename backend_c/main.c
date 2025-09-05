#include <stdio.h>
#include "graph.h"
#include "ticket.h"
#include "management.h"
#include "utils.h"

int main() {
    // Initialize the graph for routes
    Graph graph = createGraph();
    
    // Load routes from data file
    if (!loadRoutes(&graph, "data/routes.dat")) {
        fprintf(stderr, "Error loading routes.\n");
        return 1;
    }

    // Display available routes
    printf("Available Routes:\n");
    displayRoutes(&graph);

    // Ticket booking example
    Ticket ticket;
    if (bookTicket(&ticket, &graph)) {
        printf("Ticket booked successfully!\n");
    } else {
        printf("Ticket booking failed.\n");
    }

    // Ticket management example
    if (cancelTicket(&ticket)) {
        printf("Ticket cancelled successfully!\n");
    } else {
        printf("Ticket cancellation failed.\n");
    }

    // Clean up resources
    freeGraph(&graph);
    return 0;
}