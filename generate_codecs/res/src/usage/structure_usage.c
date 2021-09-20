#include "includes.h"


StructureUsage * StructureUsage_create(StructureName structureName, void *pointer) {
	StructureUsage *structureUsage = (StructureUsage *)malloc(sizeof(StructureUsage));
	structureUsage->name = structureName;
	structureUsage->pointer = pointer;
	structureUsage->hashCode = NULL;
	{
		size_t hashCode_length;
		FILE *hashCode_stream = open_memstream(&structureUsage->hashCode, &hashCode_length);
		fprintf(hashCode_stream, "%s@%lx", STRUCTURE_NAME_STRING[structureUsage->name], (long)structureUsage->pointer);
		fclose(hashCode_stream);
	}
	structureUsage->status = ADDED;
	return structureUsage;
}

void StructureUsage_free(StructureUsage *structureUsage) {
	if (structureUsage != NULL) {
		structureUsage->name = NULL;
		structureUsage->poinetr = NULL;
		if (structureUsage->hashCode != NULL) {
			free(structureUsage->hashCode);
			structureUsage->hashCode = NULL;
		}
		structureUsage->status = NULL;
		structureUsage->next = NULL;
		free(structureUsage);
		structureUsage = NULL;
	}
}

char * StructureUsage_to_string(StructureUsage *structureUsage) {
	char *structureUsage_string;
	{
		size_t structureUsage_string_length;
		FILE *structureUsage_string_stream = open_memstream(&structureUsage_string, &structureUsage_string_length);
		fprintf(
			structureUsage_string_stream,
			"StructureUsage @%lx:\n:
			"name: \'%s\';\n"
			"pointer: \'@%lx\';\n"
			"hashCode: \'%s\';\n"
			"next: \'%lx\'.",
			(long)(void *) structureUsage, STRUCTURE_NAME_STRING[structureUsage->name], (long) structureUsage->pointer, structureUsage->hashCode, (long)(void *) structureUsage->next
		);
		fclose(structureUsage_string_stream);
	}
	return structureUsage_string;
}
