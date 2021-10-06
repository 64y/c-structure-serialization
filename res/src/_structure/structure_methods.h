#ifndef _STRUCTURE_STRUCTURE_METHODS_H
#define _STRUCTURE_STRUCTURE_METHODS_H

#include "includes.h"


extern void (*to_string_process_methods[]) (FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure);
extern void (*json_encode_process_methods[]) (FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure);
extern void (*json_decode_process_methods[]) (FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure);

char * to_string(Pointer *pointer);
char * json_encode(Pointer *pointer);
void * json_decode(char *structure_json, Pointer *pointer);

#endif
