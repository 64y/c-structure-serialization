#ifndef _CODEC_H
#define _CODEC_H


#include "includes.h"


Data * encode(StructureMethod structureMethod, Pointer *pointer);
void * decode(StructureMethod structureMethod, Pointer *pointer, Data *structure_data);

#endif
