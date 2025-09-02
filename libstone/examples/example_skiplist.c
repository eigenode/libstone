#include<stdio.h>
#include<stone/skiplist.h>

int int_compare(const void* a, const void* b) { return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b); }


int main(void){
	printf("Hello, skip lists!\n");
	SkipList *sl = skiplist_create(int_compare);
	printf("SkipList has size %ld\n", skiplist_size(sl));
	printf("Size of int is %ld, size of size_t is %ld", sizeof(int), sizeof(size_t));
}
