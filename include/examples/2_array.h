#ifndef _H
#define _H

#include <stdio.h>

#include "serialization/registrate.h"
#include "serialization/serialize.h"


#include "structures/array.h"

void example_of_structure_with_array() {
	puts(" = = = Example of Structure with Array = = = ");
	
	Serialize_registrate_structure("Array", "structures/array.h");
	Serialize *array_serialize = Serialize_create("Array");
	
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
	char *array_string = array_serialize->to_string(array);
	puts(array_string);
	
	{
		Serialize_free(array_serialize);
		
		array->arr_n = 0;
		free(array->arr);
		free(array);
		
		free(array_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");
}

#endif
