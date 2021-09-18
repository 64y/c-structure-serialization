#include "includes.h"


char * pointers_to_string(char *structure_name, void *pointer) {
	StructureUsageSet *structureUsageSet = StructureUsageSet_create();
	StructureUsageSet_add(structureUsageSet, structure_name, pointer);
	
	do {
		int i=0, size = (int) structureUsageSet->size;
		for (StructureUsage *curr=structureUsageSet->head; i<size && curr!=NULL; i++, curr=curr->next) {
			if (curr->pointer==NULL) {
				curr->usage = 1;
			} else {
				StructureUsageSet_pass(structureUsageSet, curr);
			}
		}
		StructureUsageSet_stage_next(structureUsageSet);
	} while (StructureUsageSet_is_all_used(structureUsageSet)==0);
	if (structureUsageSet->size == 1) {
		StructureUsageSet_free(structureUsageSet);
		return NULL;
	}
	size_t string_length;
	char *string;
	FILE *string_stream = open_memstream(&string, &string_length);
	for (StructureUsage *curr=structureUsageSet->head->next; curr!=NULL; curr=curr->next) {
		char *structure_string = NULL;
		// %s use to_string here
		fflush(string_stream);
		if (structure_string!=NULL && strstr(string, structure_string)==NULL) {
			fprintf(string_stream, "|_ %s", structure_string);
		}
		free(structure_string);
	}
	fclose(string_stream);
	StructureUsageSet_free(structureUsageSet);
	return string;
}

void StructureUsageSet_pass(StructureUsageSet *structureUsageSet, StructureUsage *structureUsage) {
	if (structureUsage->usage==1) {
		return;
	}
	// %s use StructureUsageSet_pass_\'Structure\' cast and call here
}
