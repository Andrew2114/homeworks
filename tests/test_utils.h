#pragma once

#include <stdio.h>

#define TEST(name) void name(void)
#define ASSERT(expr)                                                  \
    do {                                                              \
        if (!(expr)) {                                                \
            printf("FAILED: %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return;                                                   \
        }                                                             \
    } while (0)
#define ASSERT_STRING_EQ(s1, s2)                                   \
    do {                                                           \
        if (strcmp(s1, s2) != 0) {                                 \
            printf("FAILED: %s:%d: expected \"%s\", got \"%s\"\n", \
                __FILE__, __LINE__, s1, s2);                       \
            return;                                                \
        }                                                          \
    } while (0)
#define RUN_TEST(test)                   \
    do {                                 \
        printf("Running %s... ", #test); \
        test();                          \
        printf("OK\n");                  \
        tests_passed++;                  \
    } while (0)

#endif
