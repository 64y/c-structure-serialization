#ifndef STRINGS_H
#define STRINGS_H


#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/boolean.h"


char * string_copy(char *string);
Boolean string_equals(char *string0, char *string1);
Boolean string_equals_r(char *string0, char *string1);
char * string_to_lower(char *string);
char * string_to_upper(char *string);
char * string_to_upper_safe(char *string);
char * string_make_shortcut(char *string);
char * string_appends(char *strings[]);
char * string_random(size_t string_length_min, size_t string_length_max);


void * array_string_create(void *element_create_arguments);
char * array_string_to_string(void *element);
void array_string_free(void *element);
int array_string_cmp(const void *a, const void *b);
Array * Array_create_for_string();

#endif
