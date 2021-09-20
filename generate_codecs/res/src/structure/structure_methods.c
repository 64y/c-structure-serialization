#include "includes.h"


void (*pass_methods[]) (StructureUsageSet *structureUsageSet, void *structure_parent, void *structure_child); = {
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


char * to_string_method(StructureUsage *structureUsage) {
	StructureUsageSet *structureUsageSet = StructureUsageSet_create();
	StructureUsageSet_add(structureUsageSet, structureUsage);
	
	do {
		int i=0, size = (int) structureUsageSet->size;
		for (StructureUsage *curr=structureUsageSet->head; i<size && curr!=NULL; i++, curr=curr->next) {
			if (curr->pointer==NULL) {
				curr->usage = USED;
			} else {
				pass_methods[curr->name](StructureUsage_create(structureUsageSet, curr));
			}
		}
		StructureUsageSet_stage_next(structureUsageSet);
	} while (StructureUsageSet_is_all_used(structureUsageSet) != USED);
	if (structureUsageSet->size == 1) {
		StructureUsageSet_free(structureUsageSet);
		return NULL;
	}
	char *string;
	{
		size_t string_length;
		FILE *string_stream = open_memstream(&string, &string_length);
		for (StructureUsage *curr=structureUsageSet->head->next; curr!=NULL; curr=curr->next) {
			char *structureUsage_string = to_string_methods[curr->name](curr->pointer);
			fflush(string_stream);
			if (structureUsage_string!=NULL && strstr(string, structureUsage_string)==NULL) {
				fprintf(string_stream, "\n\t|_ %%s", structureUsage_string);
			}
			free(structureUsage_string);
		}
		fclose(string_stream);
	}
	StructureUsageSet_free(structureUsageSet);
	return string;
}

