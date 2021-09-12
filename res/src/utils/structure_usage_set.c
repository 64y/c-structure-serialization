#include "includes.h"


StructureUsageSet * StructureUsageSet_create(void) {
	StructureUsageSet *structureUsageSet = (StructureUsageSet *)malloc(sizeof(StructureUsageSet));
	structureUsageSet->size = 0;
	structureUsageSet->head = NULL;
	structureUsageSet->stage = 0;
	return structureUsageSet;
}

void StructureUsageSet_free(StructureUsageSet *structureUsageSet) {
	if (structureUsageSet != NULL) {
		structureUsageSet->size = 0;
		if (structureUsageSet->head != NULL) {	
			StructureUsage *curr = structureUsageSet->head;
			while (curr != NULL) {
				StructureUsage *prev = curr;
				curr = curr->next;
				StructureUsage_free(prev);
			}
			structureUsageSet->head = NULL;
			structureUsageSet->stage = 0;
		}
		free(structureUsageSet);
		structureUsageSet = NULL;
	}
}

char * StructureUsageSet_to_string(StructureUsageSet *structureUsageSet) {
	char *string;
	{
		size_t string_length;
		FILE *string_stream = open_memstream(&string, &string_length);
		fprintf(string_stream, "StrucureUsageSet [%ld] {%d}:\n", structureUsageSet->size, structureUsageSet->stage);
		for (StructureUsage *curr=structureUsageSet->head; curr != NULL; curr=curr->next) {
			char *string_StructureUsage = StructureUsage_to_string(curr);
			fprintf(string_stream, "%s\n", string_StructureUsage);
			free(string_StructureUsage);
		}
		fclose(string_stream);
	}
	return string;
}

void StructureUsageSet_add(StructureUsageSet *structureUsageSet, char *name, void *pointer) {
	long address = (long) pointer;
	for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
		if (strcmp(curr->name, name)==0 && curr->address==address) {
			return;
		}
	}
	structureUsageSet->size = structureUsageSet->size + 1;
	if (structureUsageSet->head == NULL) {
		structureUsageSet->head = StructureUsage_create(name, address, pointer);
	} else {
		StructureUsage *last = structureUsageSet->head;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = StructureUsage_create(name, address, pointer);
	}
}

StructureUsage * StructureUsageSet_get(StructureUsageSet *structureUsageSet, char *name, void *pointer) {
	long address = (long) pointer;
	for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
		if (strcmp(curr->name, name)==0 && curr->address==address) {
			return curr;
		}
	}
	return NULL;
}

void StructureUsageSet_stage_next(StructureUsageSet *structureUsageSet) {
	structureUsageSet->stage = structureUsageSet->stage + 1;
}

int StructureUsageSet_is_all_used(StructureUsageSet *structureUsageSet) {
	int used = 1;
	for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
		used &= curr->usage;
	}
	return used;
}
