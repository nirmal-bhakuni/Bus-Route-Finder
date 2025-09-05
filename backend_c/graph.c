#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void initializeGraph(Graph* graph) {
    graph->stopCount = 0;
    graph->routeCount = 0;
}

bool addStop(Graph* graph, const char* stopName) {
    if (graph->stopCount >= MAX_STOPS) return false;
    strncpy(graph->stops[graph->stopCount].name, stopName, sizeof(graph->stops[graph->stopCount].name) - 1);
    graph->stops[graph->stopCount].name[sizeof(graph->stops[graph->stopCount].name) - 1] = '\0';
    graph->stops[graph->stopCount].id = graph->stopCount;
    graph->stopCount++;
    return true;
}

bool addRoute(Graph* graph, int startId, int endId, int cost, int time) {
    if (graph->routeCount >= MAX_ROUTES) return false;
    if (startId >= graph->stopCount || endId >= graph->stopCount) return false;
    Route* route = &graph->routes[graph->routeCount];
    route->start = startId;
    route->end = endId;
    route->cost = cost;
    route->time = time;
    graph->routeCount++;
    return true;
}

void displayGraph(const Graph* graph) {
    printf("Stops:\n");
    for (int i = 0; i < graph->stopCount; i++) {
        printf("  [%d] %s\n", graph->stops[i].id, graph->stops[i].name);
    }
    printf("Routes:\n");
    for (int i = 0; i < graph->routeCount; i++) {
        printf("  %s -> %s | Cost: %d | Time: %d min\n",
            graph->stops[graph->routes[i].start].name,
            graph->stops[graph->routes[i].end].name,
            graph->routes[i].cost,
            graph->routes[i].time);
    }
}

// Simple BFS for connectivity (returns true if path exists)
bool bfs(const Graph* graph, int startId, int endId) {
    if (startId >= graph->stopCount || endId >= graph->stopCount) return false;
    bool visited[MAX_STOPS] = {0};
    int queue[MAX_STOPS];
    int front = 0, rear = 0;

    visited[startId] = true;
    queue[rear++] = startId;

    while (front < rear) {
        int current = queue[front++];
        if (current == endId) return true;
        for (int i = 0; i < graph->routeCount; i++) {
            if (graph->routes[i].start == current && !visited[graph->routes[i].end]) {
                visited[graph->routes[i].end] = true;
                queue[rear++] = graph->routes[i].end;
            }
        }
    }
    return false;
}

// Simple DFS for connectivity (returns true if path exists)
bool dfs(const Graph* graph, int startId, int endId) {
    if (startId >= graph->stopCount || endId >= graph->stopCount) return false;
    bool visited[MAX_STOPS] = {0};
    int stack[MAX_STOPS];
    int top = -1;

    stack[++top] = startId;

    while (top >= 0) {
        int current = stack[top--];
        if (current == endId) return true;
        if (!visited[current]) {
            visited[current] = true;
            for (int i = 0; i < graph->routeCount; i++) {
                if (graph->routes[i].start == current && !visited[graph->routes[i].end]) {
                    stack[++top] = graph->routes[i].end;
                }
            }
        }
    }
    return false;
}