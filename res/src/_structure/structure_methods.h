#ifndef _STRUCTURE_STRUCTURE_METHODS_H
#define _STRUCTURE_STRUCTURE_METHODS_H

#include "includes.h"


extern char * (*to_string_process_methods[]) (PointerDictionary *pointerDictionary, void *structure);

extern char * (*json_encode_methods[]) (PointerDictionary *pointerDictionary, void *structure);

extern void * (*json_decode_methods[]) (PointerDictionary *pointerDictionary, char *structure_json, void *structure);


char * to_string(Pointer *pointer);

char * json_encode(Pointer *pointer);

void * json_decode(char *structure_json, Pointer *pointer);

#endif
