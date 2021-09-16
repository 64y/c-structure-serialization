#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

#include <c_structure_serialization/serializer.h>


#include "structures/array.h"

void example_of_structure_with_array() {
	puts(" = = = Example of Structure with Array = = = ");
	
	Serializer *array_serializer = Serializer_create("Array");
	
	size_t array_arr_n = 5;
	Array *array;
	{
		array = (Array *)malloc(sizeof(Array));
		array->arr_n = array_arr_n;
		array->arr = ({
			int *arr = (int *)calloc(array_arr_n, sizeof(int));
			for (int i=0; i<array_arr_n; i++) {
				arr[i] = i * 2;
			}
			arr;
		});
	}
	
	puts("TO_STRING:");
	char *array_string = array_serializer->to_string(array);
	puts(array_string);
	
	{
		Serializer_free(array_serializer);
		
		array->arr_n = 0;
		free(array->arr);
		free(array);
		
		free(array_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
}

#endif
