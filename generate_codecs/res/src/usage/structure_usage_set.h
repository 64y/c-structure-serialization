#ifndef STRUCTURE_USAGE_SET_H
#define STRUCTURE_USAGE_SET_H

#include "includes.h"


typedef struct StructureUsageSet {
	size_t size;
	StructureUsage *head;
	int stage;
} StructureUsageSet;

StructureUsageSet * StructureUsageSet_create(void);
void StructureUsageSet_free(StructureUsageSet *structureUsageSet);
char * StructureUsageSet_to_string(StructureUsageSet *structureUsageSet);
void StructureUsageSet_add(StructureUsageSet *structureUsageSet, char *name, void *pointer);
StructureUsage * StructureUsageSet_get_by_hashCode(StructureUsageSet *structureUsageSet, char *name, void *pointer);
void StructureUsageSet_stage_next(StructureUsageSet *structureUsageSet);
int StructureUsageSet_is_all_used(StructureUsageSet *structureUsageSet);
void StructureUsageSet_pass(StructureUsageSet *structureUsageSet, StructureUsage *structureUsage);

#endif
