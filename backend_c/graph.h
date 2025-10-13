// Header for graph (route management) module.

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_STOPS 100
#define MAX_NAME_LEN 50
#define MAX_EDGES_PER_STOP 50

/* Edge (route) from one stop to another */
typedef struct {
    int dest;           /* destination stop index */
    int cost;           /* travel cost */
    int time;           /* travel time in minutes */
} Edge;

/* Stop (node) in graph */
typedef struct {
    char name[MAX_NAME_LEN];
    int edgeCount;
    Edge edges[MAX_EDGES_PER_STOP];
} Stop;

/* Graph holds stops and adjacency lists */
typedef struct {
    int stopCount;
    Stop stops[MAX_STOPS];
} Graph;

/* Initialize the graph to hold up to numStops (numStops ignored - static size)
   Now accepts a pointer to the Graph to initialize. */
void initGraph(Graph* g, int numStops);

/* Add a stop with name to graph; returns true on success */
bool addStop(Graph* g, char* stopName);

/* Add a directed route from src name to dest name with cost and time */
bool addRoute(Graph* g, char* src, char* dest, int cost, int time);

/* Display all routes and stops */
void displayRoutes(Graph* g);

/* Find a route between src and dest using BFS; prints path if found */
bool findRouteBFS(Graph* g, char* src, char* dest);

/* Show nearby (directly connected) stops to given stopName */
void showNearbyStops(Graph* g, char* stopName);

#endif /* GRAPH_H */