#ifndef GENERATE_CODE_FOR_JSON_CODEC_H
#define GENERATE_CODE_FOR_JSON_CODEC_H


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


void generate_json_codec_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);
void generate_json_codec_definition(FILE *h_stream, Tabs *tabs, Structure *structure);

void json_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void json_encode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void json_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void json_decode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void json_decode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void json_decode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void json_decode_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif
