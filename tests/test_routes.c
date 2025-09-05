#include <stdio.h>
#include <assert.h>
#include "graph.h"

void test_add_route() {
    Graph* graph = create_graph();
    add_route(graph, "A", "B", 5);
    add_route(graph, "A", "C", 10);
    
    assert(get_route_cost(graph, "A", "B") == 5);
    assert(get_route_cost(graph, "A", "C") == 10);
    
    destroy_graph(graph);
}

void test_bfs() {
    Graph* graph = create_graph();
    add_route(graph, "A", "B", 5);
    add_route(graph, "B", "C", 3);
    add_route(graph, "C", "D", 2);
    
    int path_exists = bfs(graph, "A", "D");
    assert(path_exists == 1);
    
    destroy_graph(graph);
}

void test_dfs() {
    Graph* graph = create_graph();
    add_route(graph, "A", "B", 5);
    add_route(graph, "B", "C", 3);
    add_route(graph, "C", "D", 2);
    
    int path_exists = dfs(graph, "A", "D");
    assert(path_exists == 1);
    
    destroy_graph(graph);
}

int main() {
    test_add_route();
    test_bfs();
    test_dfs();
    
    printf("All tests passed!\n");
    return 0;
}