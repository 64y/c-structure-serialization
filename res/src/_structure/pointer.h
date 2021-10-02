#ifndef _STRUCTURE_POINTER_H
#define _STRUCTURE_POINTER_H


#include "includes.h"


typedef struct Pointer {
	StructureName name;
	void *pointer;
} Pointer;

Pointer * Pointer_create(StructureName name, void *structure);
void Pointer_free(Pointer *pointer);
char * Pointer_to_string(Pointer *pointer);
char * Pointer_hash_code(Pointer *pointer);

#endif
