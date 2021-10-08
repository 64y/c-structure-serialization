#ifndef GENERATE_BYTES_CODEC_H
#define GENERATE_BYTES_CODEC_H

#include "c_structure_serialization/data_types/structure.h"


char * generate_bytes_codec_declaration(Structure *structure);
char * generate_bytes_codec_definition(Structure *structure);

#endif
