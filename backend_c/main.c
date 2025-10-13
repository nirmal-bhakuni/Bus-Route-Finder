// Main program to demonstrate the Bus Route Finder modules.

#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "ticket.h"
#include "management.h"
#include "login.h"
#include "utils.h"

/* Populate sample data: stops and routes */
static void populateSampleGraph(Graph* g) {
    initGraph(0);
    addStop(g, "Central");
    addStop(g, "North");
    addStop(g, "East");
    addStop(g, "South");
    addStop(g, "West");
    addRoute(g, "Central", "North", 10, 15);
    addRoute(g, "North", "East", 12, 20);
    addRoute(g, "East", "South", 8, 12);
    addRoute(g, "South", "West", 15, 25);
    addRoute(g, "West", "Central", 9, 10);
    addRoute(g, "Central", "East", 7, 12);
}

/* Show route management menu */
static void routeMenu(Graph* g) {
    int choice;
    char src[50], dest[50], name[50];
    while (1) {
        printHeader("Route Management");
        printf("1. Display routes\n2. Find route (BFS)\n3. Show nearby stops\n4. Add stop\n5. Add route\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }
        if (choice == 0) break;
        switch (choice) {
            case 1:
                displayRoutes(g);
                break;
            case 2:
                printf("Source: "); scanf("%s", src);
                printf("Destination: "); scanf("%s", dest);
                findRouteBFS(g, src, dest);
                break;
            case 3:
                printf("Stop name: "); scanf("%s", name);
                showNearbyStops(g, name);
                break;
            case 4:
                printf("Stop name: "); scanf("%s", name);
                if (addStop(g, name)) printf("Stop added: %s\n", name);
                else printf("Could not add stop (duplicate or limit reached).\n");
                break;
            case 5:
                printf("From: "); scanf("%s", src);
                printf("To: "); scanf("%s", dest);
                printf("Cost: "); scanf("%d", &choice);
                printf("Time (min): "); scanf("%d", &choice);
                /* we read cost/time into choice twice; fix by rereading (simple) */
                {
                    int cost, time;
                    printf("Cost: "); scanf("%d", &cost);
                    printf("Time (min): "); scanf("%d", &time);
                    if (addRoute(g, src, dest, cost, time)) printf("Route added.\n");
                    else printf("Failed to add route. Check stops.\n");
                }
                break;
            default:
                printf("Invalid choice.\n");
        }
        delay(300);
    }
}

/* Show ticket menu */
static void ticketMenu(void) {
    int choice;
    char name[50], src[50], dest[50];
    while (1) {
        printHeader("Ticket Booking");
        printf("1. Book ticket\n2. Cancel ticket\n3. View tickets\n4. View available seats\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }
        if (choice == 0) break;
        switch (choice) {
            case 1:
                printf("Passenger name: "); scanf("%s", name);
                printf("From: "); scanf("%s", src);
                printf("To: "); scanf("%s", dest);
                {
                    int tid = bookTicket(name, src, dest);
                    if (tid > 0) printf("Booked. TicketID = %d\n", tid);
                    else {
                        printf("Booking failed. Adding to waiting list.\n");
                        addToWaitingList(name, src, dest);
                    }
                }
                break;
            case 2:
                {
                    int tid;
                    printf("TicketID to cancel: "); scanf("%d", &tid);
                    if (cancelTicket(tid)) {
                        printf("Ticket %d canceled.\n", tid);
                        processWaitingList(); /* try to fill freed seat */
                    } else printf("Ticket %d not found.\n", tid);
                }
                break;
            case 3:
                displayTickets();
                break;
            case 4:
                printf("Available seats: %d\n", availableSeats());
                break;
            default:
                printf("Invalid choice.\n");
        }
        delay(300);
    }
}

/* Waiting list menu */
static void waitingMenu(void) {
    int choice;
    while (1) {
        printHeader("Waiting List Management");
        printf("1. Display waiting list\n2. Process waiting list\n0. Back\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }
        if (choice == 0) break;
        switch (choice) {
            case 1:
                displayWaitingList();
                break;
            case 2:
                processWaitingList();
                break;
            default:
                printf("Invalid choice.\n");
        }
        delay(300);
    }
}

int main(void) {
    Graph g;
    g.stopCount = 0;
    initTickets();
    populateSampleGraph(&g);

    char username[50], password[50];
    int choice;

    while (1) {
        printHeader("Bus Route Finder - Main Menu");
        printf("1. Register\n2. Login\n0. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }
        if (choice == 0) break;
        if (choice == 1) {
            printf("Choose username: "); scanf("%s", username);
            printf("Choose password: "); scanf("%s", password);
            if (registerUser(username, password)) printf("Registration successful. You can login now.\n");
            else printf("Registration failed (user may exist).\n");
        } else if (choice == 2) {
            printf("Username: "); scanf("%s", username);
            printf("Password: "); scanf("%s", password);
            if (loginUser(username, password)) {
                printf("Login successful. Welcome, %s!\n", username);
                /* logged in - show submenus */
                while (1) {
                    printHeader("User Menu");
                    printf("1. Route Management\n2. Ticket Booking\n3. Waiting List\n0. Logout\nChoice: ");
                    if (scanf("%d", &choice) != 1) { while (getchar() != '\n'); continue; }
                    if (choice == 0) break;
                    switch (choice) {
                        case 1: routeMenu(&g); break;
                        case 2: ticketMenu(); break;
                        case 3: waitingMenu(); break;
                        default: printf("Invalid choice.\n");
                    }
                }
            } else {
                printf("Login failed. Check credentials.\n");
            }
        } else {
            printf("Invalid choice.\n");
        }
        delay(300);
    }

    printf("Exiting Bus Route Finder. Goodbye.\n");
    return 0;
}