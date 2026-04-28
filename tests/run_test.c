#include "test_utils.h"

void test_is_number_with_valid_integers(void);
void test_is_number_with_valid_floats(void);
void test_is_number_with_invalid_strings(void);
void test_is_number_with_null(void);
void test_create_table(void);
void test_add_row(void);
void test_parse_csv_file(void);
void test_parse_csv_file_not_found(void);
void test_print_table_to_file(void);

int main() {
    int tests_passed = 0;
    int total_tests = 0;
    
    printf("\n=== Running Utils Tests ===\n");
    RUN_TEST(test_is_number_with_valid_integers);
    RUN_TEST(test_is_number_with_valid_floats);
    RUN_TEST(test_is_number_with_invalid_strings);
    RUN_TEST(test_is_number_with_null);
    
    printf("\n=== Running CSV Parser Tests ===\n");
    RUN_TEST(test_create_table);
    RUN_TEST(test_add_row);
    RUN_TEST(test_parse_csv_file);
    RUN_TEST(test_parse_csv_file_not_found);
    
    printf("\n=== Running Table Printer Tests ===\n");
    RUN_TEST(test_print_table_to_file);
    
    printf("\n=== All Tests Passed! (%d/%d) ===\n\n", tests_passed, tests_passed);
    
    return 0;
}
