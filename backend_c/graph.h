#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_STOPS 100
#define MAX_ROUTES 50

typedef struct {
    char name[50];
    int id;
} Stop;

typedef struct {
    int start;
    int end;
    int cost;
    int time; // in minutes
} Route;

typedef struct {
    Stop stops[MAX_STOPS];
    int stopCount;
    Route routes[MAX_ROUTES];
    int routeCount;
} Graph;

// Function prototypes
void initializeGraph(Graph* graph);
bool addStop(Graph* graph, const char* stopName);
bool addRoute(Graph* graph, int startId, int endId, int cost, int time);
void displayGraph(const Graph* graph);
bool bfs(const Graph* graph, int startId, int endId);
bool dfs(const Graph* graph, int startId, int endId);

#endif // GRAPH_H