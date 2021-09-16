#include <stdlib.h>

#include "utils/basic_defines.h"
#include "data_types/data_type.h"
#include "data_types/attribute.h"


Attribute * Attribute_create(AttributeType type, char *data_type, char *name, Dimension *dimension) {
	Attribute *attribute = (Attribute *)malloc(sizeof(Attribute));
	attribute->type = type;
	attribute->data_type = string_copy(data_type);
	attribute->name = string_copy(name);
	attribute->dimension = dimension;
	attribute->next = NULL;
	return attribute;
}

void Attribute_free(Attribute *attribute) {
	if (attribute != NULL) {
		attribute->type = NO_TYPE;
		if (attribute->data_type != NULL) {
			free(attribute->data_type);
			attribute->data_type = NULL;
		}
		if (attribute->name != NULL) {
			free(attribute->name);
			attribute->name = NULL;
		}
		if (attribute->dimension != NULL) {
			Dimension_free(attribute->dimension);
			attribute->dimension = NULL;
		}
		free(attribute);
		attribute = NULL;
	}
}

char * Attribute_to_string(Attribute *attribute) {
	char *attribute_string;
	{
		size_t attribute_string_length;
		FILE *attribute_string_stream = open_memstream(&attribute_string, &attribute_string_length);
		char *dimension_string = Dimension_to_string(attribute->dimension);
		fprintf(attribute_string_stream,
			"Attribute @%lx:\n"
			"type: \'%s\';\n"
			"data type: \'%s\';\n"
			"name: \'%s\';\n"
			"dimension: @%lx;\n"
			"next: @%lx\'.\n"
			"%s",
			(long)(void *) attribute, ATTRIBUTE_TYPE_STRING[attribute->type], attribute->data_type, attribute->name, (long)(void *) attribute->dimension, (long)(void *) attribute->next, dimension_string
		);
		{
			free(dimension_string);
			fclose(attribute_string_stream);
		}
	}
	return attribute_string;
}
