#include <stdio.h>
#include <stdlib.h>

#include "utils/array.h"


Array * Array_create(void * (*create) (void *element), char * (*to_string) (void *element), void (*free) (void *element)) {
	Array *array = (Array *)malloc(sizeof(Array));
	array->a_size = 0;
	array->a = (void **)calloc(array->a_size, sizeof(void *));
	array->create = create;
	array->to_string = to_string;
	array->free = free;
	return array;
}

void Array_free(Array *array) {
	if (array != NULL) {
		for (int i=0; i<array->a_size; i++) {
			if (array->a[i] != NULL) {
				array->free(array->a[i]);
				array->a[i] = NULL;
			}
		}
		array->a_size = 0;
		free(array->a);
		array->create = NULL;
		array->to_string = NULL;
		array->free = NULL;
		free(array);
		array = NULL;
	}
}

char * Array_to_string(Array *array) {
	char *array_string;
	{
		size_t array_string_length;
		FILE *array_string_stream = open_memstream(&array_string, &array_string_length);
		fprintf(
			array_string_stream,
			"Array:\n"
			"a_size: \'%ld\';\n"
			"a: [\n",
			array->a_size
		);
		for (int i=0; i<array->a_size; i++) {
			char *string = array->to_string(array->a[i]);
			fprintf(array_string_stream, "\t%s\n", string);
			{
				free(string);
			}
		}
		fprintf(array_string_stream, "].");
		{
			fclose(array_string_stream);
		}
	}
	return array_string;
}

void Array_add(Array *array, void *element) {
	array->a = (void **)realloc(array->a, (array->a_size+1)*sizeof(void *));
	array->a[array->a_size] = array->create(element);
	array->a_size = array->a_size + 1;
}

void * Array_get(Array *array, int index) {
	return array->a[index];
}

int Array_size(Array *array) {
	return array->a_size;
}

void Array_sort(Array *array, int (*cmp) (const void *a, const void *b)) {
	qsort(array->a, array->a_size, sizeof(void *), cmp);
}
