#ifndef _POINTER_H
#define _POINTER_H


#include <stddef.h>

#include "_structure/structure_info.h"


typedef struct Pointer {
	StructureName name;
	void *pointer;
	long address;
	unsigned int address_id;
	char *hashCode;
	struct Pointer *next;
} Pointer;

Pointer * Pointer_create_by_name_pointer(StructureName name, void *structure);
Pointer * Pointer_create_by_name_pointer_address(StructureName name, void *structure, long address);
Pointer * Pointer_create_by_name_pointer_hashCode(StructureName name, void *structure, char *hashCode);
void Pointer_free(Pointer *pointer);
char * Pointer_to_string(Pointer *pointer);

#endif
