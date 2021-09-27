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
		}
		structureUsageSet->stage = 0;
		free(structureUsageSet);
		structureUsageSet = NULL;
	}
}

char * StructureUsageSet_to_string(StructureUsageSet *structureUsageSet) {
	char *structureUsageSet_string;
	{
		size_t structureUsageSet_string_length;
		FILE *structureUsageSet_string_stream = open_memstream(&structureUsageSet_string, &structureUsageSet_string_length);
		fprintf(
			structureUsageSet_string_stream,
			"StrucureUsageSet @%lx:\n"
			"size: \'%ld\';\n"
			"head: \'%lx\';\n"
			"stage: \'%d\'.",
			(long)(void  *) structureUsageSet, structureUsageSet->size, (long)(void *)structureUsageSet->head, structureUsageSet->stage
		);
		for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
			char *structureUsage_string = StructureUsage_to_string(curr);
			fprintf(structureUsageSet_string_stream, "\n\t|_ %s", structureUsage_string);
			{
				free(structureUsage_string);
			}
		}
		fclose(structureUsageSet_string_stream);
	}
	return structureUsageSet_string;
}

void StructureUsageSet_add(StructureUsageSet *structureUsageSet, StructureUsage *structureUsage) {
	for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
		if (strcmp(curr->hashCode, structureUsage->hashCode)==0) {
			StructureUsage_free(structureUsage);
			return;
		}
	}
	structureUsageSet->size = structureUsageSet->size + 1;
	if (structureUsageSet->head == NULL) {
		structureUsageSet->head = structureUsage;
	} else {
		StructureUsage *last = structureUsageSet->head;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = structureUsage;
	}
}

void StructureUsageSet_next_stage(StructureUsageSet *structureUsageSet) {
	structureUsageSet->stage = structureUsageSet->stage + 1;
}

StructureUsage * StructureUsageSet_get_by_hashCode(StructureUsageSet *structureUsageSet, char *hashCode) {
	for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
		if (strcmp(curr->hashCode, hashCode)==0) {
			return curr;
		}
	}
	return NULL;
}

StructureStatus StructureUsageSet_is_all_used(StructureUsageSet *structureUsageSet) {
	StructureStatus status = USED;
	for (StructureUsage *curr=structureUsageSet->head; curr!=NULL; curr=curr->next) {
		status &= curr->status;
	}
	return status;
}