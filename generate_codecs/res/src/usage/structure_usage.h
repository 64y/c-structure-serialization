#ifndef STRUCTURE_USAGE_H
#define STRUCTURE_USAGE_H


#include "structure/structure_name.h"
#include "structure/structure_status.h"

typedef struct StructureUsage {
	StructureName name;
	void *pointer;
	char *hashCode;
	StructureStatus status;
	struct StructureUsage *next;
} StructureUsage;

StructureUsage * StructureUsage_create(StructureName structrureName, void *pointer);
void StructureUsage_free(StructureUsage *structureUsage);
char * StructureUsage_to_string(StructureUsage *structureUsage);

#endif
