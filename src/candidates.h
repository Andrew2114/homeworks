#pragma once

typedef struct {
    int city;
    int dist;
} Candidate;

typedef struct {
    Candidate* list;
    int count;
    int capacity;
} CandidateList;

CandidateList* create_candidate_list(void);
void add_candidate(CandidateList* list, int city, int dist);
void remove_best_candidate(CandidateList* list, int* chosen_city);
int has_candidates(CandidateList* list);
void free_candidate_list(CandidateList* list);
