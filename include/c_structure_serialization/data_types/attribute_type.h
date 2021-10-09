#ifndef ATTRIBUTE_TYPE
#define ATTRIBUTE_TYPE


#include <stddef.h>


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

extern const size_t ATTRIBUTE_TYPE_STRING_SIZE;
extern const char *ATTRIBUTE_TYPE_STRING[];

#endif
