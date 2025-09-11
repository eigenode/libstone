#ifndef STN_SKIPLIST_H
#define STN_SKIPLIST_H
#define STN_SKIPLIST_MAXLEVEL (uint8_t) sizeof(size_t) * 8
#define STN_SKIPLIST_P 0.5
#include<stdlib.h>
#include<stdint.h>

typedef struct skipnode {
	void* key;
	void* value;
	struct skipnode* forward[STN_SKIPLIST_MAXLEVEL];
} stn_skipnode_t;

typedef struct {
	size_t size;
	uint8_t level;
	int (*cmp)(void *key, void* okey);
	const void* max_key;
	stn_skipnode_t* header;	
} stn_skiplist_t;

// Public interfaces
stn_skiplist_t *stn_skiplist_create(int(*cmp)(void*,void*), const void *max_key);
size_t stn_skiplist_size(stn_skiplist_t *sl);
int stn_skiplist_insert(stn_skiplist_t *sl, void* key, void* value);
void stn_skiplist_show(stn_skiplist_t *sl, void (*printkv)(void *k, void*v));
void stn_skiplist_show_levels(stn_skiplist_t *sl, void (*printkv)(void *k, void*v));

// Implementation
static stn_skipnode_t* stn_skipnode_create(void *key, void *value){
	stn_skipnode_t* sn = (stn_skipnode_t*) malloc(sizeof(*sn));
	if (sn == NULL) return sn;
	sn->key = key;
	sn->value = value;
	for (uint8_t i = 0; i < STN_SKIPLIST_MAXLEVEL; i++) sn->forward[i] = NULL;
	return sn;
} 

stn_skiplist_t *stn_skiplist_create(int (*cmp)(void*, void*), const void* max_key){
	stn_skiplist_t *sl = (stn_skiplist_t*) malloc(sizeof(*sl));
	if (sl == NULL) return NULL;
	sl->size = 0;
	sl->level = 1;
	sl->cmp = cmp;
	sl->max_key = max_key;
	sl->header = stn_skipnode_create((void*)sl->max_key, NULL);
	if (sl->header == NULL) return NULL;
	return sl;
}

size_t stn_skiplist_size(stn_skiplist_t *sl) {
	return sl->size;
}

uint8_t random_level(){
	uint8_t v = 1;
	while (( (double)rand() / RAND_MAX ) < STN_SKIPLIST_P && v < STN_SKIPLIST_MAXLEVEL) v++;
	return v;
}

int stn_skiplist_insert(stn_skiplist_t *sl, void* key, void* value){
	stn_skipnode_t *update[STN_SKIPLIST_MAXLEVEL] = { NULL };
	stn_skipnode_t *x = sl->header;
	
	for(short i = sl->level - 1; i >= 0; i--) {
		while (x->forward[i] != NULL && sl->cmp(x->forward[i]->key, key) < 0) x = x->forward[i];
		update[i] = x;
	}
	int retcode = 0;
	x = x->forward[0];
	if (x != NULL && sl->cmp(x->key, key) == 0) { 
		x->value = value; 
		retcode = 0;
	} else {
		uint8_t v = random_level();
		if (v > sl->level) {
			for (uint8_t i = sl->level; i < v; i++) update[i] = sl->header;
			sl->level = v;
		}
		x = stn_skipnode_create(key, value);
		if (x == NULL) return -1;
		sl->size++;
		retcode = 1;
		for (uint8_t i = 0; i < v; i++) {
			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}
	}
	return retcode;
}

void stn_skiplist_show(stn_skiplist_t *sl, void (*printkv)(void *k, void*v)){
	stn_skipnode_t *node = sl->header->forward[0];
    printf("Skiplist (level 0): ");
    while (node != NULL) {
        printkv(node->key, node->value);
		node = node->forward[0];
		if (node != NULL) printf(" ");
    }
    printf("\n");
}

void stn_skiplist_show_levels(stn_skiplist_t *sl, void (*printkv)(void *k, void*v)){
	for (int lvl = sl->level - 1; lvl >= 0; lvl--) {
        stn_skipnode_t *node = sl->header->forward[lvl];
        printf("Level %d: ", lvl);
        while (node != NULL) {
            printkv(node->key, node->value);
            node = node->forward[lvl];
			if (node != NULL) printf(" ");
        }
        printf("\n");
    }
}

#endif
