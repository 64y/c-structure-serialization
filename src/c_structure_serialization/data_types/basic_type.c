#include <stdio.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/basic_type.h"


char * BasicType_to_string(BasicType *basicType) {
	char *basicType_string;
	{
		size_t basicType_string_length;
		FILE *basicType_string_stream = open_memstream(&basicType_string, &basicType_string_length);
		fprintf(
			basicType_string_stream,
			"BasicType:\n"
			"name: \'%s\';\n"
			"size in bytes: \'%ld\';\n"
			"format specifier: \'%s\';\n"
			"format parameters: \'%s\'.",
			basicType->name, basicType->size_in_bytes, basicType->format_specifier, basicType->format_parameters
		);
		{
			fclose(basicType_string_stream);
		}
	}
	return basicType_string;
}

BasicType * get_basic_type_by_name(char *name) {
	for (int i=0; i<BASIC_TYPES_SIZE; i++) {
		if (string_equals(BASIC_TYPES[i].name, name)) {
			return &BASIC_TYPES[i];
		}
	}
	return NULL;
}


const size_t BASIC_TYPES_SIZE = 10;

BasicType BASIC_TYPES[] = {
	{"char", 1, "%02hhx", ""},
	{"unsigned char", 1, "%hhu", ""},
	{"byte", 1, "%hhu", ""},
	{"short", 2, "%hd", ""},
	{"int", 4, "%d", ""},
	{"unsigned", 4, "%u", ""},
	{"long", 8, "%ld", ""},
	{"float", 4, "%f", ""},
	{"double", 8, "%lf", ""},
	{"char *", 8, "%s", ""}
};
