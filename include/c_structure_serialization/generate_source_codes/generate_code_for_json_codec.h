#ifndef GENERATE_CODE_FOR_JSON_CODEC_H
#define GENERATE_CODE_FOR_JSON_CODEC_H


#include "c_structure_serialization/data_types/structure.h"


char * generate_json_codec_declaration(Structure *structure);
char * generate_json_codec_definition(Structure *structure);

#endif
