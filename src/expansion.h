#pragma once

#include "candidates.h"
#include "graph.h"

typedef struct {
    int* owner;
    int num_states;
    int total_cities;
} ExpansionResult;

ExpansionResult* expand_states(Graph* graph, int* capitals, int num_capitals);
void print_result(ExpansionResult* result);
void free_result(ExpansionResult* result);
