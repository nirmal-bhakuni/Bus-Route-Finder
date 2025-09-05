#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define MAX_STOPS 100

typedef struct {
    char name[50];
    int cost;
    int time;
} Stop;

typedef struct {
    Stop stops[MAX_STOPS];
    int adjacencyMatrix[MAX_STOPS][MAX_STOPS];
    int numStops;
} Graph;

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numStops = 0;
    memset(graph->adjacencyMatrix, 0, sizeof(graph->adjacencyMatrix));
    return graph;
}

void addStop(Graph* graph, const char* name) {
    if (graph->numStops < MAX_STOPS) {
        strcpy(graph->stops[graph->numStops].name, name);
        graph->stops[graph->numStops].cost = 0;
        graph->stops[graph->numStops].time = 0;
        graph->numStops++;
    }
}

void addRoute(Graph* graph, int from, int to, int cost, int time) {
    if (from < graph->numStops && to < graph->numStops) {
        graph->adjacencyMatrix[from][to] = 1;
        graph->stops[from].cost = cost;
        graph->stops[from].time = time;
    }
}

void bfs(Graph* graph, int start) {
    int visited[MAX_STOPS] = {0};
    int queue[MAX_STOPS];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];
        printf("Visited: %s\n", graph->stops[current].name);

        for (int i = 0; i < graph->numStops; i++) {
            if (graph->adjacencyMatrix[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

void freeGraph(Graph* graph) {
    free(graph);
}