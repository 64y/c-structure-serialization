#include <stdio.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/basic_type.h"


char * BasicType_to_string(BasicType *basicType) {
	char *basicType_string = string_create_by_format(
		"BasicType@%lX\n"
		"name: \'%s\';\n"
		"size in bytes: \'%ld\';\n"
		"format specifier: \'%s\';\n"
		"format parameters: \'%s\'.",
		(long)(void *)basicType, basicType->name, basicType->size_in_bytes, basicType->format_specifier, basicType->format_parameters
	);
	return basicType_string;
}


const size_t BASIC_TYPE_SIZE = 10;

BasicType BASIC_TYPE[] = {
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

BasicType * BasicType_get_by_name(char *name) {
	for (int i=0; i<BASIC_TYPE_SIZE; i++) {
		if (string_equals(BASIC_TYPE[i].name, name)) {
			return &BASIC_TYPE[i];
		}
	}
	return NULL;
}
