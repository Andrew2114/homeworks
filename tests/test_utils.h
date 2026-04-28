#pragma once

#include <stdio.h>
#include <string.h>

#define TEST(name) void name(void)
#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            printf("FAILED: %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return; \
        } \
    } while(0)

#define ASSERT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("FAILED: %s:%d: expected %d, got %d\n", \
                   __FILE__, __LINE__, expected, actual); \
            return; \
        } \
    } while(0)

#define RUN_TEST(test) \
    do { \
        printf("Running %s... ", #test); \
        test(); \
        printf("OK\n"); \
        tests_passed++; \
    } while(0)
