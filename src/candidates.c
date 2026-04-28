#include "candidates.h"
#include <stdlib.h>

CandidateList* create_candidate_list(void)
{
    CandidateList* list = malloc(sizeof(CandidateList));
    if (list == NULL)
        return NULL;

    list->list = NULL;
    list->count = 0;
    list->capacity = 0;
    return list;
}

void add_candidate(CandidateList* list, int city, int dist)
{
    if (list->capacity == 0) {
        list->capacity = 4;
        list->list = malloc(list->capacity * sizeof(Candidate));
        if (list->list == NULL)
            return;
    }

    if (list->count == list->capacity) {
        list->capacity *= 2;
        list->list = realloc(list->list, list->capacity * sizeof(Candidate));
        if (list->list == NULL)
            return;
    }

    list->list[list->count].city = city;
    list->list[list->count].dist = dist;
    list->count++;
}

void remove_best_candidate(CandidateList* list, int* chosen_city)
{
    if (list->count == 0)
        return;

    int best_idx = 0;
    for (int i = 1; i < list->count; i++) {
        if (list->list[i].dist < list->list[best_idx].dist) {
            best_idx = i;
        }
    }

    *chosen_city = list->list[best_idx].city;

    // Сдвигаем оставшиеся элементы
    for (int i = best_idx; i < list->count - 1; i++) {
        list->list[i] = list->list[i + 1];
    }
    list->count--;
}

int has_candidates(CandidateList* list)
{
    return list->count > 0;
}

void free_candidate_list(CandidateList* list)
{
    if (list == NULL)
        return;
    free(list->list);
    free(list);
}
