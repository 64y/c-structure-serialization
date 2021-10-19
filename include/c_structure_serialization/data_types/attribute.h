#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/dimension.h"


typedef struct Attribute {
	AttributeType type;
	char *data_type;
	char *data_type_upper;
	char *name;
	Dimension *dimension;
	struct Attribute *next;
} Attribute;

Attribute * Attribute_create(AttributeType type, char *data_type, char *name, Dimension *dimension);
void Attribute_free(Attribute *attribute);
char * Attribute_to_string(Attribute *attribute);

#endif
