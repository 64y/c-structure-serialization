#ifndef _STRUCTURE_STRUCTURE_METHODS_H
#define _STRUCTURE_STRUCTURE_METHODS_H


#include "includes.h"


typedef unsigned int enum_index;

typedef enum StructureMethods {
	TO_STRING,
	JSON_ENCODE,
	JSON_DECODE,
	BYTES_ENCODE,
	BYTES_DECODE
} StructureMethods;

extern void (*methods[][5]) (FILE *, PointerDictionary *, void *);

char * to_string(Pointer *pointer);
char * json_encode(Pointer *pointer);
void * json_decode(char *structure_json, Pointer *pointer);
Data * bytes_encode(Pointer *pointer);
void * bytes_decode(Data *structure_bytes, Pointer *pointer);

#endif
