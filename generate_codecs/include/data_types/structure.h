#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "utils/array.h"
#include "data_types/attribute.h"


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

#endif
