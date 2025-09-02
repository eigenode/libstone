#ifndef SKIPLIST_H
#define SKIPLIST_H
#define SKIPLIST_MAX_LEVEL sizeof(size_t) * 8
#include <stddef.h>
#include <stdint.h>

/**
 * A node of a skip list.
 */
struct SkipNode {
    void *key;
    void *value;
    struct SkipNode* forward[];
};

typedef struct SkipNode SkipNode;


/**
 * A skip list data structure.
 */
typedef struct {
    size_t size; // 8
	short level;
	int (*compare)(const void* key, const void* other_key);
	SkipNode *header;
} SkipList;

/**
 * Create an empty skip list.
 */
SkipList* skiplist_create(int (*compare_fn)(const void* key, const void* other_key));

/**
 * Search a given key in the skip list `sl` and return its value.
 * If the key is not present, NULL is returned instead.
 */
void* skiplist_search(SkipList* sl, void* key);

/**
 * Insert a new element in the skip list with the specified `key` and 
 * `data`. It returns 0 if the operation is sucessfull without erros, 
 * -1 otherwise.
 */
int skiplist_insert(SkipList *sl, void* key, void* data);


/**
 * Return the number of elements in the skip list;
 */
size_t skiplist_size(SkipList *sl);

#endif

