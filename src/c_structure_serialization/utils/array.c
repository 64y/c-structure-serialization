#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/array.h"


Array * Array_create(
	void * (*element_create) (void *element_create_arguments),
	void (*element_free) (void *element),
	char * (*element_to_string) (void *element)
) {
	Array *array = (Array *)malloc(sizeof(Array));
	array->size = 0;
	array->elements = (void **)calloc(array->size, sizeof(void *));
	array->element_create = element_create;
	array->element_free = element_free;
	array->element_to_string = element_to_string;
	return array;
}

void Array_free(Array *array) {
	if (array!=NULL) {
		if (array->elements!=NULL) {
			for (int i=0; i<array->size; i++) {
				if (array->elements[i]!=NULL) {
					array->element_free(array->elements[i]);
					array->elements[i] = NULL;
				}
			}
			array->size = 0;
			free(array->elements);
			array->elements = NULL;
		}
		array->element_create = NULL;
		array->element_free = NULL;
		array->element_to_string = NULL;
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
			"Array@%lX\n"
			"a_size: \'%ld\';\n"
			"a: [\n",
			(long)(void *)array, array->size
		);
		for (int i=0; i<array->size; i++) {
			char *element_string = array->element_to_string(array->elements[i]);
			fprintf(array_string_stream, "  %s\n", element_string);
			{
				free(element_string);
			}
		}
		fprintf(array_string_stream, "].");
		{
			fclose(array_string_stream);
		}
	}
	return array_string;
}


void Array_add(Array *array, void *element_create_arguments) {
	array->elements = (void **)realloc(array->elements, (array->size+1)*sizeof(void *));
	array->elements[array->size] = array->element_create(element_create_arguments);
	array->size = array->size+1;
}

void * Array_get(Array *array, int index) {
	return array->elements[index];
}

size_t Array_size(Array *array) {
	return array->size;
}

void Array_sort(Array *array, int (*cmp) (const void *a, const void *b)) {
	qsort(array->elements, array->size, sizeof(void *), cmp);
}
