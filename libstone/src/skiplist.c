#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<stone/skiplist.h>


SkipList *skiplist_create(int (*compare)(const void *key, const void *other_key)){
	SkipList *sl = (SkipList*) malloc(sizeof(*sl));
	if (sl == NULL) return NULL;
	sl->size = 0;
	sl->level = 0;
	sl->compare = compare;
	sl->header = (SkipNode*) malloc(sizeof(SkipNode) + SKIPLIST_MAX_LEVEL * sizeof(SkipNode*));
	sl->header->key = NULL;
	sl->header->value = NULL;
	for (size_t i = 0; i < SKIPLIST_MAX_LEVEL; i++) sl->header->forward[i] = NULL; 
	printf("Size of the skip list is %ld bytes, %ld bytes\n", sizeof(sl), sizeof(*sl));
	return sl; 
}

size_t skiplist_size(SkipList *sl) { return sl->size; }

int skiplist_insert(SkipList* sl, void* key, void* data){
	SkipNode *update[SKIPLIST_MAX_LEVEL] = { NULL };
	SkipNode *x = sl->header;
	for(uint8_t i = sl->level; i > 0; i--) {
		while (x->key != NULL && sl->compare(x->forward[i-1]->key, key) < 0) x = x->forward[i-1];
		// x->key < searchKey <= x->forward[i-1]->key
		update[i-1] = x;	
	}
	x = x->forward[1];
	printf("data is: %p\n", data);
	printf("Update is: %p\n", update);
	return 0;	
}
