#pragma once

#include <stdio.h>
#include <string.h>

#define TEST(name) void name(void)

#define ASSERT(expr)                                                  \
    do {                                                              \
        if (!(expr)) {                                                \
            printf("FAILED: %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return;                                                   \
        }                                                             \
    } while (0)

#define ASSERT_STR_EQ(expected, actual)                            \
    do {                                                           \
        if (strcmp(expected, actual) != 0) {                       \
            printf("FAILED: %s:%d: expected \"%s\", got \"%s\"\n", \
                __FILE__, __LINE__, expected, actual);             \
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
