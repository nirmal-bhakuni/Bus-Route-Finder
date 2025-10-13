// Implementation of ticket management (waiting list) module.

#include <stdio.h>
#include <string.h>
#include "management.h"
#include "ticket.h"

typedef struct {
    char name[MAX_NAME_LEN];
    char src[MAX_NAME_LEN];
    char dest[MAX_NAME_LEN];
    int used;
} WaitEntry;

static WaitEntry waitlist[MAX_WAITLIST];
static int wait_front = 0;
static int wait_rear = 0;
static int wait_count = 0;

/* Add to waiting list (simple circular queue) */
void addToWaitingList(char* name, char* src, char* dest) {
    if (wait_count >= MAX_WAITLIST) {
        printf("Waiting list full. Cannot add %s\n", name);
        return;
    }
    int idx = wait_rear;
    strncpy(waitlist[idx].name, name, MAX_NAME_LEN - 1);
    waitlist[idx].name[MAX_NAME_LEN - 1] = '\0';
    strncpy(waitlist[idx].src, src, MAX_NAME_LEN - 1);
    waitlist[idx].src[MAX_NAME_LEN - 1] = '\0';
    strncpy(waitlist[idx].dest, dest, MAX_NAME_LEN - 1);
    waitlist[idx].dest[MAX_NAME_LEN - 1] = '\0';
    waitlist[idx].used = 1;
    wait_rear = (wait_rear + 1) % MAX_WAITLIST;
    wait_count++;
    printf("%s added to waiting list (position %d)\n", name, wait_count);
}

/* Process waiting list: try to book tickets for queued people while seats available */
void processWaitingList(void) {
    int processed = 0;
    while (wait_count > 0 && availableSeats() > 0) {
        WaitEntry *e = &waitlist[wait_front];
        if (!e->used) {
            /* should not happen, skip */
            wait_front = (wait_front + 1) % MAX_WAITLIST;
            wait_count--;
            continue;
        }
        int tid = bookTicket(e->name, e->src, e->dest);
        if (tid > 0) {
            printf("Waiting passenger %s assigned TicketID %d\n", e->name, tid);
            e->used = 0;
            wait_front = (wait_front + 1) % MAX_WAITLIST;
            wait_count--;
            processed++;
        } else {
            /* booking failed (no seat or other) */
            break;
        }
    }
    if (processed == 0) {
        printf("No waiting passengers processed.\n");
    }
}

/* Display waiting list in order */
void displayWaitingList(void) {
    if (wait_count == 0) {
        printf("Waiting list is empty.\n");
        return;
    }
    printf("Waiting List (%d):\n", wait_count);
    int idx = wait_front;
    for (int i = 0; i < wait_count; i++) {
        WaitEntry* e = &waitlist[idx];
        printf("  %d. %s | From: %s | To: %s\n", i + 1, e->name, e->src, e->dest);
        idx = (idx + 1) % MAX_WAITLIST;
    }
}