#include "includes.h"


void (*pass_methods[]) (StructureUsageSet *structureUsageSet, StructureUsage *structureUsage) = {
	%s
};

char * (*to_string_methods[]) (void *structure) = {
	%s
};

char * (*json_encode_methods[]) (void *structure) = {
	%s
};

void * (*json_decode_methods[]) (char *structure_json) = {
	%s
};

StructureUsageSet * walk_through_pointer(StructureName structureName, void *pointer) {
	StructureUsageSet *structureUsageSet = StructureUsageSet_create();
	StructureUsageSet_add(structureUsageSet, StructureUsage_create(structureName, pointer));
	do {
		int i=0, size = (int) structureUsageSet->size;
		for (StructureUsage *curr=structureUsageSet->head; i<size && curr!=NULL; i++, curr=curr->next) {
			if (curr->pointer==NULL) {
				curr->status = USED;
			} else {
				pass_methods[curr->name](structureUsageSet, curr);
			}
		}
		StructureUsageSet_next_stage(structureUsageSet);
	} while (StructureUsageSet_is_all_used(structureUsageSet) != USED);
	return structureUsageSet;
}

char * to_string_method(StructureName structureName, void *pointer) {
	StructureUsageSet *structureUsageSet = walk_through_pointer(structureName, pointer);
	char *pointer_string;
	{
		size_t pointer_string_length;
		FILE *pointer_string_stream = open_memstream(&pointer_string, &pointer_string_length);
		
		char *structureUsage_string = to_string_methods[structureUsageSet->head->name](structureUsageSet->head->pointer);
		fprintf(pointer_string_stream, "%%s", structureUsage_string);
		free(structureUsage_string); structureUsage_string = NULL;
		
		for (StructureUsage *curr=structureUsageSet->head->next; curr!=NULL; curr=curr->next) {
			if (curr->pointer == NULL) {
				continue;
			}
			structureUsage_string = to_string_methods[curr->name](curr->pointer);
			fprintf(pointer_string_stream, "  |_ %%s", structureUsage_string);
			free(structureUsage_string);
		}
		fclose(pointer_string_stream);
	}
	StructureUsageSet_free(structureUsageSet);
	return pointer_string;
}
