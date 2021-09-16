#ifndef ARRAY_OF_H
#define ARRAY_OF_H

#include "utils/array.h"
#include "data_types/structure.h"


void * array_string_create(void *element);
char * array_string_to_string(void *element);
void array_string_free(void *element);
int array_string_cmp(const void *a, const void *b);
Array * Array_of_string_create();


void * array_Structure_arguments(char *file_path, Array *source_code);
void * array_Structure_create(void *element);
char * array_Structure_to_string(void *element);
void array_Structure_free(void *element);
Array * Array_of_Structure_create();

#endif
