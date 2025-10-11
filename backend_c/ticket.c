#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ticket.h"

static int ticketid=1000;
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