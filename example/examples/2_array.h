#ifndef $2_ARRAY_H
#define $2_ARRAY_H


#include "structures/array.h"
#include "examples/example_template.h"

void * Array_create(void);
void Array_free(void *structure);

void example_of_structure_with_array(int DO_FLAGS) {
	example(
		"Structure with Array",
		"./my_lib",
		"Array",
		Array_create,
		Array_free,
		DO_FLAGS
	);
}

void * Array_create(void) {
	int array_arr_n = 10;
	Array *array = (Array *)malloc(sizeof(Array));
	array->arr_n = array_arr_n;
	array->arr = (int *)calloc(array_arr_n, sizeof(int));
	array->arr[0] = 1;
	array->arr[1] = 1;
	for (int i=2; i<array_arr_n; i++) {
		array->arr[i] = array->arr[i-2] + array->arr[i-1];
	}
	return array;
}

void Array_free(void *structure) {
	Array *array = (Array *) structure;
	if (array != NULL) {
		array->arr_n = 0;
		if (array->arr != NULL) {
			free(array->arr);
			array->arr = NULL;
		}
		free(array);
		array = NULL;
	}
}

#endif
