#ifndef STRINGS_H
#define STRINGS_H


#include <stdarg.h>
#include <stdbool.h>

#include "c_structure_serialization/utils/array.h"


#define NO_MORE_STRINGS NULL


char * string_create(char *string);
char * string_create_by_format(char *format, ...);
void string_free(char *string);

bool string_equals(char *stringA, char *stringB);
bool string_ends_with(char *string, char *end);

char * string_copy(char *string);
char * string_to_lower(char *string);
char * string_to_upper(char *string);
char * string_replace_char(char *string, char find, char replace);
char * string_appends(char *first_string, ...);

char * string_make_shortcut(char *string);
char * string_repeat_star(size_t times);


void * array_string_create(va_list string_arguments);
char * array_string_to_string(void *string);
void array_string_free(void *string);
int array_string_cmp(const void *a, const void *b);
Array * Array_create_for_string();



#endif
