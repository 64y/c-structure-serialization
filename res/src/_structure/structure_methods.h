#ifndef STRUCTURE_METHODS_H
#define STRUCTURE_METHODS_H

#include "includes.h"


extern void (*pass_methods[]) (StructureUsageSet *structureUsageSet, StructureUsage *structureUsage); 

extern char * (*to_string_methods[]) (void *structure);

extern char * (*json_encode_methods[]) (void *structure);

extern void * (*json_decode_methods[]) (char *structure_json);

StructureUsageSet * walk_through_pointer(StructureName structureName, void *pointer);

char * to_string_method(StructureName structureName, void *pointer);

#endif
