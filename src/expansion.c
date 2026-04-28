#include "expansion.h"
#include <stdio.h>
#include <stdlib.h>

static void initialize_owners(int* owner, int* capitals, int num_capitals, int total_cities) {
    for (int i = 0; i < total_cities; i++) {
        owner[i] = -1;
    }
    for (int i = 0; i < num_capitals; i++) {
        owner[capitals[i]] = i;
    }
}

static void add_neighbors_to_candidates(Graph* graph, CandidateList** candidates, 
                                        int* owner, int city, int state) {
    Edge* edge = graph->adjacency[city];
    while (edge != NULL) {
        if (owner[edge->to] == -1) {
            add_candidate(candidates[state], edge->to, edge->len);
        }
        edge = edge->next;
    }
}

ExpansionResult* expand_states(Graph* graph, int* capitals, int num_capitals) {
    int total_cities = graph->num_vertices;
    
    ExpansionResult* result = malloc(sizeof(ExpansionResult));
    if (result == NULL) return NULL;
    
    result->owner = malloc(total_cities * sizeof(int));
    result->num_states = num_capitals;
    result->total_cities = total_cities;
    
    if (result->owner == NULL) {
        free(result);
        return NULL;
    }
    
    initialize_owners(result->owner, capitals, num_capitals, total_cities);
    
     CandidateList** candidates = malloc(num_capitals * sizeof(CandidateList*));
    for (int i = 0; i < num_capitals; i++) {
        candidates[i] = create_candidate_list();
    }
    
     for (int state = 0; state < num_capitals; state++) {
        add_neighbors_to_candidates(graph, candidates, result->owner, 
                                   capitals[state], state);
    }
    
    int total_occupied = num_capitals;
    int current_state = 0;
    
     while (total_occupied < total_cities) {
        if (has_candidates(candidates[current_state])) {
            int chosen_city;
            remove_best_candidate(candidates[current_state], &chosen_city);
            
            if (result->owner[chosen_city] == -1) {
                result->owner[chosen_city] = current_state;
                total_occupied++;
                
                add_neighbors_to_candidates(graph, candidates, result->owner,
                                           chosen_city, current_state);
            }
        }
        current_state = (current_state + 1) % num_capitals;
    }
    
     for (int i = 0; i < num_capitals; i++) {
        free_candidate_list(candidates[i]);
    }
    free(candidates);
    
    return result;
}

void print_result(ExpansionResult* result) {
    for (int state = 0; state < result->num_states; state++) {
        printf("State %d: ", state);
        for (int city = 0; city < result->total_cities; city++) {
            if (result->owner[city] == state) {
                printf("%d ", city);
            }
        }
        printf("\n");
    }
}

void free_result(ExpansionResult* result) {
    if (result == NULL) return;
    free(result->owner);
    free(result);
}
