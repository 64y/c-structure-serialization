#ifndef _CODEC_H
#define _CODEC_H


#include "_structure/structure_info.h"
#include "_structure/pointer.h"
#include "_utils/data.h"


Data * encode(StructureMethod structureMethod, Pointer *pointer);
void * decode(StructureMethod structureMethod, Pointer *pointer, Data *structure_data);

#endif
