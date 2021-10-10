#include "includes.h"


PointerNode * PointerNode_create_by_key_and_value(char *key, Pointer *value) {
	PointerNode *pointerNode = (PointerNode *)malloc(sizeof(PointerNode));
	pointerNode->key = (char *)calloc(strlen(key)+1, sizeof(char)); strcpy(pointerNode->key, key);
	pointerNode->value = value;
	pointerNode->next = NULL;
	return pointerNode;
}

PointerNode * PointerNode_create_by_value(Pointer *value) {
	char *key = Pointer_hash_code(value);
	PointerNode *pointerNode = PointerNode_create_by_key_and_value(key, value);
	{
		free(key);
	}
	return pointerNode;
}

void PointerNode_free(PointerNode *pointerNode) {
	if(pointerNode!=NULL) {
		if (pointerNode->key!=NULL) {
			free(pointerNode->key);
			pointerNode->key = NULL;
		}
		if (pointerNode->value!=NULL) {
			Pointer_free(pointerNode->value);
			pointerNode->value = NULL;
		}
		pointerNode->next = NULL;
		free(pointerNode);
		pointerNode = NULL;
	}
}

char * PointerNode_to_string(PointerNode *pointerNode) {
	char *pointerNode_string;
	{
		size_t pointerNode_string_length;
		FILE *pointerNode_string_stream = open_memstream(&pointerNode_string, &pointerNode_string_length);
		fprintf(
			pointerNode_string_stream,
			"PointerNode@%lX\n"
			"key: \'%s\';\n"
			"value: \'Pointer@%lX\';\n"
			"next: \'PointerNode@%lX\'.",
			(long)(void *)pointerNode, pointerNode->key, (long)(void *)pointerNode->value, (long)(void *)pointerNode->next
		);
		if (pointerNode->value != NULL) {
			char *pointerNode_value_string = Pointer_to_string(pointerNode->value);
			fprintf(pointerNode_string_stream, "\n  %s", pointerNode_value_string);
			{
				free(pointerNode_value_string);
			}
		}
		{
			fclose(pointerNode_string_stream);
		}
	}
	return pointerNode_string;
}


PointerDictionary * PointerDictionary_create(void) {
	PointerDictionary *pointerDictionary = (PointerDictionary *)malloc(sizeof(PointerDictionary));
	pointerDictionary->size = 0;
	pointerDictionary->head = NULL;
	pointerDictionary->stage = 0;
	return pointerDictionary;
}

void PointerDictionary_free(PointerDictionary *pointerDictionary) {
	if (pointerDictionary!=NULL) {
		pointerDictionary->size = 0;
		if (pointerDictionary->head!=NULL) {
			while (pointerDictionary->head!=NULL) {
				PointerNode *pointerNode = pointerDictionary->head;
				pointerDictionary->head = pointerDictionary->head->next;
				PointerNode_free(pointerNode);
				pointerNode = NULL;
			}
		}
		pointerDictionary->stage = 0;
		free(pointerDictionary);
		pointerDictionary = NULL;
	}
}

char * PointerDictionary_to_string(PointerDictionary *pointerDictionary) {
	char *pointerDictionary_string;
	{
		size_t pointerDictionary_string_length;
		FILE *pointerDictionary_string_stream = open_memstream(&pointerDictionary_string, &pointerDictionary_string_length);
		fprintf(
			pointerDictionary_string_stream,
			"PointerDictionary@%lX\n"
			"size: \'%ld\';\n"
			"head: \'PointerNode@%lX\';\n"
			"stage: \'%ld\'.",
			(long)(void  *)pointerDictionary, pointerDictionary->size, (long)(void *)pointerDictionary->head, pointerDictionary->stage
		);
		for (PointerNode *curr=pointerDictionary->head; curr!=NULL; curr=curr->next) {
			char *pointerNode_string = PointerNode_to_string(curr);
			fprintf(pointerDictionary_string_stream, "\n  |_ %s", pointerNode_string);
			{
				free(pointerNode_string);
			}
		}
		{
			fclose(pointerDictionary_string_stream);
		}
	}
	return pointerDictionary_string;
}


size_t PointerDictionary_size(PointerDictionary *pointerDictionary) {
	return pointerDictionary->size;
}


Pointer * PointerDictionary_get(PointerDictionary *pointerDictionary, char *key) {
	for (PointerNode *curr=pointerDictionary->head; curr!=NULL; curr=curr->next) {
		if (strcmp(key, curr->key)==0) {
			return curr->value;
		}
	}
	return NULL;
}

Boolean PointerDictionary_put_by_key_and_value(PointerDictionary *pointerDictionary, char *key, Pointer *value) {
	if (PointerDictionary_contains(pointerDictionary, key)) {
		return false;
	}
	pointerDictionary->size = pointerDictionary->size + 1;
	PointerNode *pointerNode = PointerNode_create_by_key_and_value(key, value);
	if (pointerDictionary->head==NULL) {
		pointerDictionary->head = pointerNode;
	} else {
		PointerNode *last = pointerDictionary->head;
		while (last->next!=NULL) {
			last = last->next;
		}
		last->next = pointerNode;
	}
	return true;
}

Boolean PointerDictionary_put_by_value(PointerDictionary *pointerDictionary, Pointer *value) {
	char *key = Pointer_hash_code(value);
	Boolean result = PointerDictionary_put_by_key_and_value(pointerDictionary, key, value);
	{
		free(key);
	}
	return result;
}

Boolean PointerDictionary_contains(PointerDictionary *pointerDictionary, char *key) {
	for (PointerNode *curr=pointerDictionary->head; curr!=NULL; curr=curr->next) {
		if (strcmp(key, curr->key)==0) {
			return true;
		}
	}
	return false;
}

Pointer * PointerDictionary_remove(PointerDictionary *pointerDictionary, char *key) {
	Pointer *pointer = NULL;
	if (pointerDictionary->head!=NULL) {
		if (strcmp(key, pointerDictionary->head->key)==0) {
			pointerDictionary->size = pointerDictionary->size - 1;
			PointerNode *pointerNode = pointerDictionary->head;
			pointerDictionary->head = pointerDictionary->head->next;
			pointerNode->next = NULL;
			pointer = pointerNode->value;
			PointerNode_free(pointerNode);
		} else {
			for (PointerNode *prev=pointerDictionary->head, *curr=prev->next; curr!=NULL; prev=curr, curr=curr->next) {
				if (strcmp(key, curr->key)==0) {
					pointerDictionary->size = pointerDictionary->size - 1;
					prev->next = curr->next;
					curr->next = NULL;
					pointer = curr->value;
					PointerNode_free(curr);
					break;
				}
			}
		}
	}
	return pointer;
}


void PointerDictionary_stage_next(PointerDictionary *pointerDictionary) {
	pointerDictionary->stage = pointerDictionary->stage + 1;
}
