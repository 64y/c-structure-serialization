#ifndef STRUCTURE_H
#define STRUCTURE_H


#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/data_types/attribute.h"


typedef struct Structure {
	char *file_path;
	char *name;
	char *name_lower;
	char *name_upper;
	char *shortcut;
	size_t size;
	Attribute *head;
} Structure;

Structure * Structure_create_by_file_path_and_name(char *file_path, char *name);
Structure * Structure_create_by_file_path_and_source_code(char *file_path, Array *source_code);
void Structure_free(Structure *structure);
char * Structure_to_string(Structure *structure);

void Structure_add(Structure *structure, Attribute *attribute);
bool Structure_delete(Structure *structure, Attribute *attribute);
bool Structure_contains_string_attributes(Structure *structure);
bool Structure_contains_array_attributes(Structure *structure);
bool Structure_contains_structure_attributes(Structure *structure);


void * array_Structure_create(va_list structure_arguments);
char * array_Structure_to_string(void *structure);
void array_Structure_free(void *structure);
Array * Array_create_for_Structure();

#endif
