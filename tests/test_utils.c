#include "../src/utils.h"
#include "test_utils.h"
#include <string.h>

TEST(test_is_number_with_valid_integers) {
    ASSERT(is_number("123") == 1);
    ASSERT(is_number("0") == 1);
    ASSERT(is_number("-123") == 1);
    ASSERT(is_number("-0") == 1);
}

TEST(test_is_number_with_valid_floats) {
    ASSERT(is_number("123.456") == 1);
    ASSERT(is_number("0.5") == 1);
    ASSERT(is_number("-123.456") == 1);
    ASSERT(is_number("-0.5") == 1);
}

TEST(test_is_number_with_invalid_strings) {
    ASSERT(is_number("") == 0);
    ASSERT(is_number("abc") == 0);
    ASSERT(is_number("123abc") == 0);
    ASSERT(is_number("123.456.789") == 0);
    ASSERT(is_number(".") == 0);
    ASSERT(is_number("-") == 0);
    ASSERT(is_number("-.5") == 0);
}

TEST(test_is_number_with_null) {
    ASSERT(is_number(NULL) == 0);
}
