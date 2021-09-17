#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>


typedef struct Array {
	size_t a_size;
	void **a;
	void * (*create) (void *element);
	char * (*to_string) (void *element);
	void (*free) (void *element);
} Array;

Array * Array_create(void * (*create) (void *element), char * (*to_string) (void *element), void (*free) (void *element));
void Array_free(Array *array);
char * Array_to_string(Array *array);
void Array_add(Array *array, void *element);
void * Array_get(Array *array, int index);
int Array_size(Array *array);
void Array_sort(Array *array, int (*cmp) (const void *a, const void *b));

#endif
