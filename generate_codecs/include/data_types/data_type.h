#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct BasicType {
	char *name;
	size_t size_in_bytes;
	char *format_specifier;
	char *format_parameters;
} BasicType;

char * BasicType_to_string(BasicType *basicType);


extern const int BASIC_TYPES_SIZE;
extern BasicType BASIC_TYPES[];

BasicType * get_basic_type_by_name(char *name);


typedef enum AttributeType {
	NO_TYPE,
	PRIMITIVE, 
	STRING,
	STRUCTURE,
	STRUCTURE_POINTER,
	PRIMITIVE_ARRAY,
	STRING_ARRAY,
	STRUCTURE_ARRAY,
	STRUCTURE_POINTER_ARRAY
} AttributeType;

extern const int ATTRIBUTE_TYPE_STRING_SIZE;
extern const char *ATTRIBUTE_TYPE_STRING[];

#endif
