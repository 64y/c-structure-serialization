#ifndef STRUCTURE_H
#define STRUCTURE_H


#include <stddef.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/boolean.h"
#include "c_structure_serialization/data_types/attribute.h"


typedef struct Structure {
	char *file_path;
	char *name;
	char *shortcut;
	size_t size;
	Attribute *head;
} Structure;

Structure * Structure_create_by_file_path_and_name(char *file_path, char *name);
Structure * Structure_create_by_file_path_and_source_code(char *file_path, Array *source_code);
void Structure_free(Structure *structure);
char * Structure_to_string(Structure *structure);

void Structure_add(Structure *structure, Attribute *attribute);
Boolean Structure_delete(Structure *structure, Attribute *attribute);
Boolean Structure_has_structure_attributes(Structure *structure);


void * array_Structure_create_pack_arguments(char *file_path, Array *source_code);
void * array_Structure_create(void *element_ar);
char * array_Structure_to_string(void *element);
void array_Structure_free(void *element);
Array * Array_create_for_Structure();

#endif
