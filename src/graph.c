#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph* create_graph(int n) {
    Graph* g = malloc(sizeof(Graph));
    if (g == NULL) return NULL;
    
    g->num_vertices = n;
    g->adjacency = malloc(n * sizeof(Edge*));
    if (g->adjacency == NULL) {
        free(g);
        return NULL;
    }
    
    for (int i = 0; i < n; i++) {
        g->adjacency[i] = NULL;
    }
    
    return g;
}

void add_edge(Graph* g, int from, int to, int len) {
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->len = len;
    newEdge->next = g->adjacency[from];
    g->adjacency[from] = newEdge;
}

void free_graph(Graph* g) {
    if (g == NULL) return;
    
    for (int i = 0; i < g->num_vertices; i++) {
        Edge* current = g->adjacency[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->adjacency);
    free(g);
}

void print_graph(Graph* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d: ", i);
        Edge* e = g->adjacency[i];
        while (e != NULL) {
            printf("->%d(%d) ", e->to, e->len);
            e = e->next;
        }
        printf("\n");
    }
}
