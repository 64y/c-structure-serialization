#ifndef SERIALIZE_REGISTRATE_H
#define SERIALIZE_REGISTRATE_H

#include "data_types/structure.h"


void Serialize_registrate_structure(char *name, char *file_name);

char * serialize_method_pass_declaration(Structure *structure);
char * serialize_method_pass_definition(Structure *structure);

char * serialize_method_to_string_declaration(Structure *structure);
char * serialize_method_to_string_definition(Structure *structure);

char * serialize_method_json_encode_declaration(Structure *structure);
char * serialize_method_json_encode_definition(Structure *structure);

char * serialize_method_json_decode_declaration(Structure *structure);
char * serialize_method_json_decode_definition(Structure *structure);

#endif
