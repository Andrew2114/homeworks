#include "test_utils.h"

void test_create_candidate_list(void);
void test_add_candidate(void);
void test_remove_best_candidate(void);
void test_has_candidates(void);

int main() {
    int tests_passed = 0;
    
    printf("\n=== Testing Candidate System ===\n");
    RUN_TEST(test_create_candidate_list);
    RUN_TEST(test_add_candidate);
    RUN_TEST(test_remove_best_candidate);
    RUN_TEST(test_has_candidates);
    
    printf("\n=== All Tests Passed! (%d/%d) ===\n\n", tests_passed, tests_passed);
    return 0;
}
