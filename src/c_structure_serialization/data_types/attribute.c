#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"


Attribute * Attribute_create(AttributeType type, char *data_type, char *name, Dimension *dimension) {
	Attribute *attribute = (Attribute *)malloc(sizeof(Attribute));
	attribute->type = type;
	attribute->data_type = string_copy(data_type);
	attribute->data_type_upper = string_to_upper(attribute->data_type);
	attribute->name = string_copy(name);
	attribute->dimension = dimension;
	attribute->next = NULL;
	return attribute;
}

void Attribute_free(Attribute *attribute) {
	if (attribute!=NULL) {
		attribute->type = NO_TYPE;
		if (attribute->data_type!=NULL) {
			string_free(attribute->data_type);
		}
		if (attribute->data_type_upper!=NULL) {
			string_free(attribute->data_type_upper);
		}
		if (attribute->name!=NULL) {
			string_free(attribute->name);
		}
		if (attribute->dimension!=NULL) {
			Dimension_free(attribute->dimension);
			attribute->dimension = NULL;
		}
		free(attribute);
		attribute = NULL;
	}
}

char * Attribute_to_string(Attribute *attribute) {
	char *dimension_string = Dimension_to_string(attribute->dimension);
	char *attribute_string = string_create_by_format(
		"Attribute@%lX\n"
		"type: \'%s\';\n"
		"data type: \'%s\';\n"
		"data type_upper: \'%s\';\n"
		"name: \'%s\';\n"
		"dimension: \'Dimension@%lX\';\n"
		"next: \'Attribute@%lX\'.\n"
		"%s",
		(long)(void *)attribute, ATTRIBUTE_TYPE_STRING[attribute->type], attribute->data_type, attribute->data_type_upper, attribute->name, (long)(void *)attribute->dimension, (long)(void *)attribute->next, dimension_string
	);
	{
		string_free(dimension_string);
	}
	return attribute_string;
}
