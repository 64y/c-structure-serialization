#ifndef DATA_TYPE_H
#define DATA_TYPE_H


#include <stddef.h>


typedef struct BasicType {
	char *name;
	size_t size_in_bytes;
	char *format_specifier;
	char *format_parameters;
} BasicType;

char * BasicType_to_string(BasicType *basicType);


extern const size_t BASIC_TYPE_SIZE;
extern BasicType BASIC_TYPE[];
BasicType * BasicType_get_by_name(char *name);

#endif
