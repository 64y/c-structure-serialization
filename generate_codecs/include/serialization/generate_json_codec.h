#ifndef GENERATE_JSON_CODEC_H
#define GENERATE_JSON_CODEC_H


#include "data_types/structure.h"


char * generate_json_encode_declaration(Structure *structure);
char * generate_json_encode_definition(Structure *structure);

char * generate_json_decode_declaration(Structure *structure);
char * generate_json_decode_definition(Structure *structure);

#endif
