#include "includes.h"


StructureUsage * StructureUsage_create(char *name, long address, void *pointer) {
	StructureUsage *structureUsage = (StructureUsage *)malloc(sizeof(StructureUsage));
	structureUsage->name = (char *)calloc(strlen(name)+1, sizeof(char));
	strcpy(structureUsage->name, name);
	structureUsage->address = address;
	structureUsage->pointer = pointer;
	structureUsage->usage = 0;
	return structureUsage;
}

void StructureUsage_free(StructureUsage *structureUsage) {
	if (structureUsage != NULL) {
		if (structureUsage->name != NULL) {
			free(structureUsage->name);
			structureUsage->name = NULL;
		}
		structureUsage->address = 0;
		structureUsage->pointer = NULL;
		structureUsage->usage = 0;
		structureUsage->next = NULL;
		free(structureUsage);
		structureUsage = NULL;
	}
}

char * StructureUsage_to_string(StructureUsage *structureUsage) {
	char *string;
	{
		size_t string_length;
		FILE *string_stream = open_memstream(&string, &string_length);
		fprintf(string_stream, "StructureUsage:\nName: \'%s\'\nAddress: \'@%lx\'\nUsage: \'%d\'\n", structureUsage->name, structureUsage->address, structureUsage->usage);
		fclose(string_stream);
	}
	return string;
}
