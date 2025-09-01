#include <stdio.h>
#include <stdlib.h>
#include <stone/skiplist.h>

/* Simple assert macro */
#define ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "Test failed: %s\n", msg); \
            return 1; \
        } \
    } while(0)

/* Test function */
int test_one_is_not_two() {
    ASSERT(1 != 2, "1 should be different then 2");
    return 0; // success
}

/* Main function runs all tests */
int main(void) {
    int failed = 0;

    failed += test_one_is_not_two() != 0;

    if (failed) {
        printf("Some tests failed.\n");
        return 1;
    } else {
        printf("All tests passed.\n");
        return 0;
    }
}

