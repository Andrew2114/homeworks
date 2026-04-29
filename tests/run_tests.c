#include "test_utils.h"

void test_avl_insert_and_find(void);
void test_avl_delete(void);
void test_avl_count(void);
void test_avl_contains(void);
void test_trim(void);
void test_is_valid_iata_code(void);

int main()
{
    int tests_passed = 0;

    printf("\n=== Testing AVL Tree ===\n");
    RUN_TEST(test_avl_insert_and_find);
    RUN_TEST(test_avl_delete);
    RUN_TEST(test_avl_count);
    RUN_TEST(test_avl_contains);

    printf("\n=== Testing Utils ===\n");
    RUN_TEST(test_trim);
    RUN_TEST(test_is_valid_iata_code);

    printf("\n=== All Tests Passed! (%d/%d) ===\n\n", tests_passed, tests_passed);
    return 0;
}
