#ifndef GENERATE_BYTE_CODEC_H
#define GENERATE_BYTE_CODEC_H


#include "c_structure_serialization/data_types/structure.h"


char * generate_byte_codec_declaration(Structure *structure);
char * generate_byte_codec_definition(Structure *structure);

#endif
