#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ticket.h"

static int next_ticket_id=1000;
BookingList* create_booking_list() {
     
// This function creates a new booking list. It's the first thing we must do!
    BookingList* list = (BookingList*)malloc(sizeof(BookingList));

    if (list == NULL) {
        printf("Error: CRITICAL FAILURE! Memory allocation failed for booking list!\n");
        return NULL;
    }

    list->head =NULL;
    list->totalBookings=0;
    return list;
}


// This function searches through the seats array for the FIRST free seat (a '0').
int find_free_seat(const Route* route){
if (route == NULL) {
        printf("Error:Invalid route!\n");
        return -1;
    }
    for(int i=0;i<route->totalSeats;i++){
        if(route->seats[i]==0){
            return i+1;
        }
    }
 return -1;
}


// This function is for counting how many seats are NOT taken ('0's).
int get_available_seats(const Route*route){

    if(route==NULL){
        printf("EROOR; ROUTE NOT FOUND\n");
        return 0;
    }
    int c=0;
    for(int i=0;i<route->totalSeats;i++){
        if(route->seats[i]==0){
            c++;
        }
    }
return c;
}


//Helper function to add a new booking to the linked list.
void insert_booking(BookingList* bookings,int ticketId,int routeId,const char* passengerName,int seatNumber){

     printf("Creating a new BookingNode...\n");

    BookingNode* n=(BookingNode*)malloc(sizeof(BookingNode));
       
    if(n==NULL){
            printf("Error: Could not allocate memory");
          }

       n->ticketId = ticketId;
       n->routeId = routeId;
       strcpy(n->passengerName, passengerName);
       n->seatNumber = seatNumber;
       n->isActive = true;
       n->next = bookings->head;

   bookings->head = n;
   bookings->totalBookings = bookings->totalBookings + 1;

    printf("Booking successfull!!!! \n");
}


// This function searches the linked list for a matching ticket ID.
BookingNode* search_booking(BookingList* bookings, int ticketId) {

    if (bookings == NULL) {
        printf("Error: Bookings list is EMPTY!!\n");
        return NULL;
    }
    
    BookingNode* current = bookings->head; 

    while (current != NULL) {
        if (current->ticketId == ticketId) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// =================================
// BOOKING FUNCTION
// =================================
                             
bool book_ticket(Ticket* ticket,RouteCollection* collection,BookingList* bookings){


    //EDGE CASE
  if(collection==NULL || collection->routeCount==0){
  printf("Sorry! No routes are available in the system right now. Booking is impossible.\n");
        return false;
  }


  //EDGE CASE
if(ticket->routeId<0 || ticket->routeId>=collection->routeCount){
        printf("Error: Route ID %d is completely invalid!\n", ticket->routeId);
        printf("Please choose a route that actually exists (0 to %d)\n", collection->routeCount - 1);
        return false;
}


Route *route =&collection->routes[ticket->routeId];
printf("searching for available seats on routes %s to %s....\n",route->starting_point,route->destination);

    int seatNumber = find_free_seat(route);

    if (seatNumber == -1) {
      
        printf("\n========================================\n");
        printf("BOOKING FAILED! (All Seats Taken!)\n");
        printf("========================================\n");
      
        printf("Sorry! All seats are already booked on the %s to %s route.\n", route->starting_point, route->destination);
        return false;
    }
    
  
    printf("GREAT NEWS! Found a free seat: Seat number %d!\n", seatNumber);
    
    route->seats[seatNumber - 1] = 1;  // 1 means now booked!
    printf("Seat is successfully marked as booked in the route's seat array.\n");

    
    ticket->id = next_ticket_id;
    next_ticket_id = next_ticket_id + 1; // Increment for the next customer!
    ticket->isActive = true;

    //Adding Booking To ll
    printf("Finalizing booking and adding the record to the system's linked list...\n");
   
    insert_booking(bookings, ticket->id, ticket->routeId,
                    ticket->passengerName, seatNumber);
    
    int remainingSeats = get_available_seats(route);

 printf("\n========================================\n");
    printf("          BOOKING SUCCESSFUL!           \n");
    printf("========================================\n");
    printf("Ticket ID:       %d (SAVE THIS NUMBER!)\n", ticket->id);
    printf("Passenger Name:  %s\n", ticket->passengerName);
    printf("Route:           %s to %s\n", route->starting_point, route->destination);
    printf("Seat Number:     %d (CONGRATULATIONS!)\n", seatNumber);
    printf("Ticket Price:    Rs. %.2f\n", route->cost);
    printf("Remaining Seats: %d out of %d\n", remainingSeats, route->totalSeats);
    printf("========================================\n");
    
    return true;
}



// =================================
// The Cancellation Function
// =================================


bool cancel_ticket(Ticket* ticket, RouteCollection* collection, BookingList* bookings) {

//EDGE CASE
    if (ticket == NULL || collection == NULL || bookings == NULL) {
        printf("Error: One or more critical pointers (Ticket/RouteCollection/Bookings) is NULL. Cannot proceed with cancellation.\n");
        return false;
    }

//FINDING RECORD
    printf("Starting search for booking record with Ticket ID %d...\n", ticket->id);
    BookingNode* booking = search_booking(bookings, ticket->id);


     //EDGE
    if (booking == NULL) {
        printf("\n========================================\n");
        printf("CANCELLATION FAILED! (Ticket Not Found)\n");
        printf("========================================\n");
        printf("Ticket ID %d was not found in the system. Are you sure you booked it?\n", ticket->id);
        return false;
    }
    
    printf("Ticket found for passenger %s!\n", booking->passengerName);


    //CR0SS CHECK STATUS
    if (booking->isActive == false) {
        printf("\n========================================\n");
        printf("CANCELLATION FAILED! (Already Cancelled)\n");
        printf("========================================\n");
        printf("Ticket ID %d is already cancelled. You cannot cancel a cancelled ticket!\n", ticket->id);
        return false;
    }


    Route* route = &collection->routes[booking->routeId];
    
    printf("Processing the actual seat release...\n");
   
    route->seats[booking->seatNumber - 1] = 0;  // SEAT IS VACCANT NOW!!

    printf("Seat number %d is now FREE and ready for a new booking!\n", booking->seatNumber);
    
   
    booking->isActive = false;//UPDATE
    ticket->isActive = false; //UPDATE

    
    int availableSeats = get_available_seats(route);


    printf("\n========================================\n");
    printf("         CANCELLATION SUCCESSFUL!         \n");
    printf("========================================\n");
    printf("Ticket ID:       %d\n", ticket->id);
    printf("Passenger Name:  %s\n", booking->passengerName);
    printf("Seat Number:     %d (Released!)\n", booking->seatNumber);
    printf("Route:           %s to %s\n", route->starting_point, route->destination);
    printf("Available Seats: %d out of %d (More space now!)\n", availableSeats, route->totalSeats);
    printf("========================================\n");
    printf("A full refund will be processed (eventually).\n");
    
    return true;
}



// This function displays the seat layout 

void display_seat_status(const Route* route) {
    

    if (route == NULL) {
        printf("Error: Cannot display seat status for a NULL Route!\n");
        return;
    }
    
    printf("\n======================================================\n");
      printf("              SEAT AVAILABILITY STATUS            \n");
      printf("======================================================\n");


    printf("Route: %s to %s (Route ID: %d)\n", route->starting_point, route->destination, route->id);
    
    int available = get_available_seats(route);
    printf("Total Seats: %d | Available: %d | Booked: %d\n",route->totalSeats,available,route->totalSeats-available);
            
    printf("\n");


    printf("Seat Layout:\n");
    printf("([ F ] = FREE ||  [ B ] = BOOKED)\n\n");
    printf("SEATING PLAN (Front to Back):\n");

    printf("======================================================\n");
    
    
    int seats_per_row = 4; //layout: 2 seats | AISLE | 2 seats

    printf("                [ DRIVER ]\n");
    printf("------------------------------------------------------\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < route->totalSeats; i++) {
   
        char status = (route->seats[i] == 0) ? 'F' : 'B';

        int seat_num = i + 1;
        printf("[S%02d:%c] ", seat_num, status);


       // The Aisle
        if (seat_num % 4 == 2) {
            printf("   |   ");
        }
        
        // next row
        if (seat_num % 4 == 0) {
            printf("\n");
        }
        
        //edge
        if (seat_num == route->totalSeats) {
            printf("\n");
        }
    }
    
    printf("======================================================\n");
}



// This function displays all bookings by traversing the whole linked list!

void display_all_bookings(const BookingList* bookings, const RouteCollection* collection) {
    
    if (bookings == NULL || collection == NULL) {
        printf("Error: Cannot display bookings. Bookings List or RouteCollection is NULL.\n");
        return;
    }
    
    //EDGE
    if (bookings->head == NULL)
     {
        printf("\n========================================\n");
        printf("The booking list is EMPTY! No records found.\n");
        printf("========================================\n");

        return;
    }
    

    printf("\n========================================\n");
    printf("          ALL BOOKING RECORDS             \n");
    printf("========================================\n");
    printf("Total Number of Bookings in the system: %d\n", bookings->totalBookings);
    printf("========================================\n\n");
    
    
    BookingNode* current = bookings->head;

    int bookingNumber = 1;
    
    while (current != NULL) {
  
        const Route* route = &collection->routes[current->routeId];
        
        printf("--- Booking Record #%d ---\n", bookingNumber);
        printf("Ticket ID:       %d (Unique)\n", current->ticketId);
        printf("Passenger Name:  %s\n", current->passengerName);     
        printf("Route:           %s -> %s\n", route->starting_point, route->destination);
        printf("Seat Number:     %d\n", current->seatNumber);
        
        //status
        if (current->isActive == true)
         {
            printf("Status:          ACTIVE (Confirmed!)\n");
        }
         else
          {
            printf("Status:          CANCELLED (Refund pending...)\n");
        }
        
        printf("Ticket Price:    Rs. %.2f\n", route->cost);
        printf("Distance:        %d km\n", route->distance);
        printf("Duration:        %d minutes\n\n", route->duration);
        
       
        current = current->next;
        bookingNumber = bookingNumber + 1;
    }
    
    printf("========================================\n");
    printf("Successfully reached the end of the list.\n");
    printf("========================================\n");

}


//freeing function 
void free_booking_list(BookingList* bookings) {
    
    if (bookings == NULL) 
    {
        printf("Warning: The bookings list is already NULL. Nothing to free!\n");
        return;
    }
    
    printf("Processing full memory cleanup for the booking list...\n");
    
    BookingNode* current = bookings->head;
    BookingNode* next; 
    
    int Count = 0;
    
    while (current != NULL)
    {
        next = current->next;

        free(current);
        Count = Count + 1;
        
        current = next;
    }
    
    printf("Freed a total of %d booking records (good job!).\n",Count);
    
    free(bookings);

    printf("Booking list memory cleanup COMPLETE!\n");
}