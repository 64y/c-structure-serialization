#ifndef _POINTER_SET_H
#define _POINTER_SET_H


#include "includes.h"


typedef struct PointerSet {
	size_t size;
	Pointer *head;
	size_t stage;
} PointerSet;

PointerSet * PointerSet_create(void);
PointerSet * PointerSet_create_by_head(Pointer *head);
void PointerSet_free(PointerSet *pointerSet);
char * PointerSet_to_string(PointerSet *pointerSet);

Pointer * PointerSet_get_by_hashCode(PointerSet *pointerSet, char *hashCode);
bool PointerSet_put(PointerSet *pointerSet, Pointer *pointer);
bool PointerSet_contains_by_hashCode(PointerSet *pointerSet, char *hashCode);
Pointer * PointerSet_remove_by_hashCode(PointerSet *pointerSet, char *hashCode);
void PointerSet_stage_next(PointerSet *pointerSet);

void PointerSet_walk(PointerSet *pointerSet);

#endif
