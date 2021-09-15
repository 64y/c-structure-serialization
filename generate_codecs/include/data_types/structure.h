#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "data_types/attribute.h"


typedef struct Structure {
	char *file_name;
	char *name;
	char *shortcut;
	size_t size;
	Attribute *head;
} Structure;

Structure * Structure_create(char *name, char *file_name);
void Structure_free(Structure *structure);
char * Structure_to_string(Structure *structure);

void Structure_add(Structure *structure, Attribute *attribute);
Boolean Structure_delete(Structure *structure, Attribute *attribute);
Boolean Structure_has_structure_attributes(Structure *structure);

#endif
