#ifndef _STRUCTURE_INFO_H
#define _STRUCTURE_INFO_H


#include "includes.h"


extern const size_t STRUCTURE_NAME_SIZE;

typedef enum {
	%s
} StructureName;

extern const char *STRUCTURE_NAME_STRING[];


typedef enum StructureMethod {
	TO_STRING,
	JSON_ENCODE,
	JSON_DECODE,
	BYTES_ENCODE,
	BYTES_DECODE
} StructureMethod;

extern void (*structures_methods[5][%d]) (FILE *structure_codec_stream, PointerSet *pointerSet, Pointer *pointer);

#endif
