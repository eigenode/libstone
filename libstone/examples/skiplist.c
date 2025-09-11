#include <stdio.h>
#include <limits.h>
#include <stone/skiplist.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

static const int int_max = INT_MAX;

int int_cmp(void *key, void *okey) {
    return *(int*) key - *(int*)okey;
}

void printkv(void *k, void *v) {
    printf("(%d: %c)", *(int*)k, *(char*)v);
}

void stn_skiplist_free(stn_skiplist_t *sl) {
    stn_skipnode_t *x = sl->header;
    while (x != NULL) {
        stn_skipnode_t *next = x->forward[0];

        // free keys only for non-header nodes
        if (x != sl->header && x->key != NULL) {
            free(x->key);
        }

        free(x);
        x = next;
    }
    free(sl);
}

int main(void) {
    printf("Hello, world!\n");

    // Benchmark sizes
    int elements[5] = {100000, 200000, 400000, 800000, 1600000};

    // Seed RNG once
    srand((unsigned)time(NULL));

    for (int i = 0; i < 5; i++) {
        printf("Generating %d numbers\n", elements[i]);
        stn_skiplist_t *sl = stn_skiplist_create(int_cmp, &int_max);
        printf("Created skip list size: %ld\n", stn_skiplist_size(sl));

        clock_t start = clock();

        for (int j = 0; j < elements[i]; j++) {
            int *num = malloc(sizeof(int));
            if (!num) {
                fprintf(stderr, "malloc failed\n");
                exit(1);
            }
            *num = j;  // unique keys
            stn_skiplist_insert(sl, num, NULL);
        }

        clock_t end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Elapsed CPU time: %.6f seconds for %d elements\n",
               elapsed, elements[i]);

        stn_skiplist_free(sl);
    }

    return 0;
}

