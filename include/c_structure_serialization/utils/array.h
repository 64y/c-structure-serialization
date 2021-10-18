#ifndef ARRAY_H
#define ARRAY_H


#include <stdarg.h>
#include <stddef.h>


typedef struct Array {
	size_t size;
	void **elements;
	void * (*element_create) (va_list element_arguments);
	char * (*element_to_string) (void *element);
	void (*element_free) (void *element);
} Array;

Array * Array_create(void * (*element_create) (va_list element_arguments), void (*element_free) (void *element), char * (*element_to_string) (void *element));
void Array_free(Array *array);
char * Array_to_string(Array *array);


void Array_add(Array *array, ...);
void Array_put(Array *array, void *element);
void * Array_get(Array *array, int index);
size_t Array_size(Array *array);
void Array_sort(Array *array, int (*cmp) (const void *a, const void *b));

#endif
