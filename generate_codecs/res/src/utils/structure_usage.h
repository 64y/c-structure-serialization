#ifndef STRUCTURE_USAGE_H
#define STRUCTURE_USAGE_H


typedef struct StructureUsage {
	char *name;
	long address;
	void *pointer;
	int usage;
	struct StructureUsage *next;
} StructureUsage;

StructureUsage * StructureUsage_create(char *name, long address, void *pointer);
void StructureUsage_free(StructureUsage *structureUsage);
char * StructureUsage_to_string(StructureUsage *structureUsage);

#endif
