#pragma once

typedef struct Edge {
    int to;
    int len;
    struct Edge* next;
} Edge;

typedef struct {
    Edge** adjacency;
    int num_vertices;
} Graph;

Graph* create_graph(int n);
void add_edge(Graph* g, int from, int to, int len);
void free_graph(Graph* g);
void print_graph(Graph* g);
