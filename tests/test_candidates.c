#include "../src/candidates.h"
#include "test_utils.h"

TEST(test_create_candidate_list)
{
    CandidateList* list = create_candidate_list();
    ASSERT(list != NULL);
    ASSERT_EQ(0, list->count);
    ASSERT_EQ(0, list->capacity);
    free_candidate_list(list);
}

TEST(test_add_candidate)
{
    CandidateList* list = create_candidate_list();
    add_candidate(list, 5, 100);
    ASSERT_EQ(1, list->count);
    ASSERT_EQ(4, list->capacity);
    ASSERT_EQ(5, list->list[0].city);
    ASSERT_EQ(100, list->list[0].dist);
    free_candidate_list(list);
}

TEST(test_remove_best_candidate)
{
    CandidateList* list = create_candidate_list();
    add_candidate(list, 1, 100);
    add_candidate(list, 2, 50);
    add_candidate(list, 3, 75);

    int chosen;
    remove_best_candidate(list, &chosen);
    ASSERT_EQ(2, chosen);
    ASSERT_EQ(2, list->count);

    free_candidate_list(list);
}

TEST(test_has_candidates)
{
    CandidateList* list = create_candidate_list();
    ASSERT(has_candidates(list) == 0);
    add_candidate(list, 1, 10);
    ASSERT(has_candidates(list) == 1);
    free_candidate_list(list);
}
