#ifndef _STRUCTURE_POINTER_DICTIONARY_H
#define _STRUCTURE_POINTER_DICTIONARY_H


#include "includes.h"


typedef struct PointerNode {
	char *key;
	Pointer *value;
	struct PointerNode *next;
} PointerNode;

PointerNode * PointerNode_create_by_key_and_value(char *key, Pointer *value);
PointerNode * PointerNode_create_by_value(Pointer *value);
void PointerNode_free(PointerNode *pointerNode);
char * PointerNode_to_string(PointerNode *pointerNode);


typedef struct PointerDictionary {
	size_t size;
	PointerNode *head;
	size_t stage;
} PointerDictionary;

PointerDictionary * PointerDictionary_create(void);
void PointerDictionary_free(PointerDictionary *pointerDictionary);
char * PointerDictionary_to_string(PointerDictionary *pointerDictionary);

size_t PointerDictionary_size(PointerDictionary *pointerDictionary);

Pointer * PointerDictionary_get(PointerDictionary *pointerDictionary, char *key);
Boolean PointerDictionary_put_by_key_and_value(PointerDictionary *pointerDictionary, char *key, Pointer *value);
Boolean PointerDictionary_put_by_value(PointerDictionary *pointerDictionary, Pointer *value);
Boolean PointerDictionary_contains(PointerDictionary *pointerDictionary, char *key);
Pointer * PointerDictionary_remove(PointerDictionary *pointerDictionary, char *key);

void PointerDictionary_stage_next(PointerDictionary *pointerDictionary);

#endif
