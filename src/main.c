#include "graph.h"
#include "expansion.h"
#include <stdio.h>
#include <stdlib.h>

int read_input(Graph** graph, int** capitals, int* num_capitals) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        return -1;
    }
    
    *graph = create_graph(n);
    if (*graph == NULL) return -1;
    
    for (int i = 0; i < m; i++) {
        int u, v, len;
        if (scanf("%d %d %d", &u, &v, &len) != 3) {
            return -1;
        }
        add_edge(*graph, u, v, len);
        add_edge(*graph, v, u, len);
    }
    
    int k;
    if (scanf("%d", &k) != 1) {
        return -1;
    }
    
    *capitals = malloc(k * sizeof(int));
    if (*capitals == NULL) return -1;
    
    for (int i = 0; i < k; i++) {
        if (scanf("%d", &(*capitals)[i]) != 1) {
            free(*capitals);
            return -1;
        }
    }
    
    *num_capitals = k;
    return 0;
}

int main() {
    Graph* graph = NULL;
    int* capitals = NULL;
    int num_capitals = 0;
    
    if (read_input(&graph, &capitals, &num_capitals) != 0) {
        printf("Error reading input\n");
        return -1;
    }
    
    ExpansionResult* result = expand_states(graph, capitals, num_capitals);
    if (result == NULL) {
        printf("Error during expansion\n");
        free_graph(graph);
        free(capitals);
        return -1;
    }
    
    print_result(result);
    
    free_result(result);
    free_graph(graph);
    free(capitals);
    
    return 0;
}
