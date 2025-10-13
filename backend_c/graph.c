// Implementation of graph (route management) module.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/* Initialize graph */
void initGraph(int numStops) {
    (void)numStops; /* parameter unused; array is static */
    /* set stopCount to zero */
    /* ...existing code... */
}

/* Helper: get index of stop by name, returns -1 if not found */
static int getStopIndex(const Graph* g, const char* name) {
    for (int i = 0; i < g->stopCount; i++) {
        if (strcmp(g->stops[i].name, name) == 0) return i;
    }
    return -1;
}

/* Add a stop by name */
bool addStop(Graph* g, char* stopName) {
    if (!g || !stopName) return false;
    if (g->stopCount >= MAX_STOPS) return false;
    /* prevent duplicates */
    if (getStopIndex(g, stopName) != -1) return false;
    strncpy(g->stops[g->stopCount].name, stopName, MAX_NAME_LEN - 1);
    g->stops[g->stopCount].name[MAX_NAME_LEN - 1] = '\0';
    g->stops[g->stopCount].edgeCount = 0;
    g->stopCount++;
    return true;
}

/* Add a directed route from src to dest */
bool addRoute(Graph* g, char* src, char* dest, int cost, int time) {
    if (!g || !src || !dest) return false;
    int s = getStopIndex(g, src);
    int d = getStopIndex(g, dest);
    if (s == -1 || d == -1) return false;
    if (g->stops[s].edgeCount >= MAX_EDGES_PER_STOP) return false;
    Edge* e = &g->stops[s].edges[g->stops[s].edgeCount++];
    e->dest = d;
    e->cost = cost;
    e->time = time;
    return true;
}

/* Display all stops and routes */
void displayRoutes(Graph* g) {
    if (!g) return;
    printf("Stops (%d):\n", g->stopCount);
    for (int i = 0; i < g->stopCount; i++) {
        printf("  [%d] %s\n", i, g->stops[i].name);
    }
    printf("\nRoutes:\n");
    for (int i = 0; i < g->stopCount; i++) {
        for (int j = 0; j < g->stops[i].edgeCount; j++) {
            Edge* e = &g->stops[i].edges[j];
            printf("  %s -> %s | Cost: %d | Time: %d min\n",
                g->stops[i].name,
                g->stops[e->dest].name,
                e->cost, e->time);
        }
    }
}

/* Find route using BFS and print path */
bool findRouteBFS(Graph* g, char* src, char* dest) {
    if (!g || !src || !dest) return false;
    int s = getStopIndex(g, src);
    int d = getStopIndex(g, dest);
    if (s == -1 || d == -1) return false;
    if (s == d) {
        printf("Source and destination are the same: %s\n", src);
        return true;
    }

    int queue[MAX_STOPS];
    int front = 0, rear = 0;
    int visited[MAX_STOPS];
    int prev[MAX_STOPS];

    for (int i = 0; i < MAX_STOPS; i++) {
        visited[i] = 0;
        prev[i] = -1;
    }

    visited[s] = 1;
    queue[rear++] = s;

    bool found = false;
    while (front < rear) {
        int cur = queue[front++];
        for (int i = 0; i < g->stops[cur].edgeCount; i++) {
            int to = g->stops[cur].edges[i].dest;
            if (!visited[to]) {
                visited[to] = 1;
                prev[to] = cur;
                queue[rear++] = to;
                if (to == d) {
                    found = true;
                    front = rear; /* break outer loop */
                    break;
                }
            }
        }
    }

    if (!found) {
        printf("No route found from %s to %s\n", src, dest);
        return false;
    }

    /* reconstruct path using a stack (array) */
    int stack[MAX_STOPS];
    int top = 0;
    int cur = d;
    while (cur != -1) {
        stack[top++] = cur;
        cur = prev[cur];
    }
    printf("Route found (%d stops):\n", top);
    for (int i = top - 1; i >= 0; i--) {
        printf("  %s", g->stops[stack[i]].name);
        if (i > 0) printf(" ->");
    }
    printf("\n");
    return true;
}

/* Show directly connected stops from given stop */
void showNearbyStops(Graph* g, char* stopName) {
    if (!g || !stopName) return;
    int s = getStopIndex(g, stopName);
    if (s == -1) {
        printf("Stop '%s' not found.\n", stopName);
        return;
    }
    if (g->stops[s].edgeCount == 0) {
        printf("No nearby stops found for %s\n", stopName);
        return;
    }
    printf("Nearby stops from %s:\n", stopName);
    for (int i = 0; i < g->stops[s].edgeCount; i++) {
        Edge* e = &g->stops[s].edges[i];
        printf("  - %s (Cost: %d, Time: %d min)\n",
            g->stops[e->dest].name, e->cost, e->time);
    }
}