#include "includes.h"


PointerSet * PointerSet_create(void) {
	PointerSet *pointerSet = (PointerSet *)malloc(sizeof(PointerSet));
	pointerSet->size = 0;
	pointerSet->head = NULL;
	pointerSet->stage = 0;
	pointerSet->address_id_counter = 0;
	return pointerSet;
}

PointerSet * PointerSet_create_by_head(Pointer *head) {
	PointerSet *pointerSet = (PointerSet *)malloc(sizeof(PointerSet));
	pointerSet->size = 1;
	pointerSet->head = head;
	pointerSet->stage = 0;
	pointerSet->address_id_counter = 0;
	return pointerSet;
}

void PointerSet_free(PointerSet *pointerSet) {
	if (pointerSet!=NULL) {
		pointerSet->size = 0;
		if (pointerSet->head!=NULL) {
			while (pointerSet->head!=NULL) {
				Pointer *pointer = pointerSet->head;
				pointerSet->head = pointerSet->head->next;
				Pointer_free(pointe);
			}
		}
		pointerSet->stage = 0;
		free(pointerSet);
		pointerSet = NULL;
	}
}

char * PointerSet_to_string(PointerSet *pointerSet) {
	char *pointerSet_string;
	{
		size_t pointerSet_string_length;
		FILE *pointerSet_string_stream = open_memstream(&pointerSet_string, &pointerSet_string_length);
		fprintf(
			pointerSet_string_stream,
			"PointerSet@%lX\n"
			"size: \'%ld\';\n"
			"head: \'Pointers@%lX\';\n"
			"stage: \'%ld\';"
			"address_id_counter: \'%u\'.\n",
			(long)(void  *)pointerSet, pointerSet->size, (long)(void *)pointerSet->head, pointerSet->stage, pointerSet->address_id_counter
		);
		for (Pointer *curr=pointerSet->head; curr!=NULL; curr=curr->next) {
			char *pointer_string = Pointer_to_string(curr);
			fprintf(pointerSet_string_stream, "\n  |_ %s", pointer_string);
			{
				free(pointer_string);
			}
		}
		{
			fclose(pointerSet_string_stream);
		}
	}
	return pointerSet_string;
}


bool PointerSet_add(PointerSet *pointerSet, Pointer *pointer) {
	if (PointerSet_contains(pointerSet, pointer)) {
		return false;
	}
	pointerSet->size = pointerSet->size + 1;
	pointerSet->address_id_counter = pointerSet->address_id_counter + 1;
	pointer->address_id = pointerSet->address_id_counter;
	if (pointerSet->head==NULL) {
		pointerSet->head = pointer;
	} else {
		Pointer *last = pointerSet->head;
		while (last->next!=NULL) {
			last = last->next;
		}
		last->next = pointer;
	}
	return true;
}

Pointer * PointerSet_get_by_hashCode(PointerSet *pointerSet, char *hashCode) {
	for (Pointer *curr=pointerSet->head; curr!=NULL; curr=curr->next) {
		if (strcmp(hashCode, curr->hashCode)==0) {
			return curr;
		}
	}
	return NULL;
}

bool PointerSet_contains_by_hashCode(PointerSet *pointerSet, char *hashCode) {
	return (PointerSet_get_by_hashCode(pointerSet, hashCode)!=NULL)?true:false;
}

Pointer * PointerSet_remove_by_hashCode(PointerSet *pointerSet, char *hashCode) {
	Pointer *pointer = NULL;
	if (pointerSet->head!=NULL) {
		if (strcmp(hashCode, pointerSet->head->hashCode)==0) {
			pointer = pointerSet->head;
			pointerSet->head = pointerSet->head->next;
			pointer->next = NULL;
		} else {
			for (Pointer *prev=pointerSet->head, *curr=prev->next; curr!=NULL; prev=curr, curr=curr->next) {
				if (strcmp(hashCode, curr->hashCode)==0) {
					prev->next = curr->next;
					pointer = curr;
					pointer->next = NULL;
					break;
				}
			}
		}
	}
	if (pointer!=NULL) {
		pointerSet->size = pointerSet->size - 1;
	}
	return pointer;
}

void PointerSet_stage_next(PointerSet *pointerSet) {
	pointerSet->stage = pointerSet->stage + 1;
}
