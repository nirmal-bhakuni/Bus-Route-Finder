// ticket.h
#ifndef TICKET_H
#define TICKET_H

#include "graph.h"
#include <stdbool.h>

#define MAX_NAME 100
#define MAX_ROUTES 50
#define MAX_SEATS 60


// Represents a single travel route between two points
typedef struct {
    int id;
    char starting_point[MAX_NAME]; 
    char destination[MAX_NAME];
    int distance;
    double cost;
    int duration;
    int totalSeats;
    int seats[MAX_SEATS];
} Route;

// Container for storing multiple routes
typedef struct {
    Route routes[MAX_ROUTES];
    int routeCount;
} RouteCollection;

typedef struct BookingNode {
    int ticketId;
    int routeId;
    char passengerName[MAX_NAME];
    int seatNumber;
    bool isActive;
    struct BookingNode* next;
} BookingNode;

typedef struct {
    BookingNode* head;
    int totalBookings;
} BookingList;

typedef struct {
    int id;
    int routeId;
    char passengerName[MAX_NAME];
    bool isActive;
} Ticket;

// Function declarations
BookingList* create_booking_list();
bool book_ticket(Ticket* ticket, RouteCollection* collection, BookingList* bookings);
bool cancel_ticket(Ticket* ticket, RouteCollection* collection, BookingList* bookings);
BookingNode* search_booking(BookingList* bookings, int ticketId);
void display_seat_status(const Route* route);
void display_all_bookings(const BookingList* bookings, const RouteCollection* collection);
void free_booking_list(BookingList* bookings);
int find_free_seat(const Route* route);
int get_available_seats(const Route* route);


//EXTRAS
Route* find_route_by_id(const RouteCollection* collection, int routeId);
int increment_ticket_id();

#endif