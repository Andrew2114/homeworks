#include "test_utils.h"
#include "../src/utils.h"

TEST(test_trim)
{
    char str1[] = "  hello  ";
    trim(str1);
    ASSERT_STR_EQ("hello", str1);

    char str2[] = "no spaces";
    trim(str2);
    ASSERT_STR_EQ("no spaces", str2);

    char str3[] = "   ";
    trim(str3);
    ASSERT_STR_EQ("", str3);
}

TEST(test_is_valid_iata_code)
{
    ASSERT(is_valid_iata_code("SVO") == 1);
    ASSERT(is_valid_iata_code("JFK") == 1);
    ASSERT(is_valid_iata_code("A12") == 1);
    ASSERT(is_valid_iata_code("AB") == 0);
    ASSERT(is_valid_iata_code("ABCD") == 0);
    ASSERT(is_valid_iata_code("") == 0);
    ASSERT(is_valid_iata_code(NULL) == 0);
    ASSERT(is_valid_iata_code("AB$") == 0);
}
