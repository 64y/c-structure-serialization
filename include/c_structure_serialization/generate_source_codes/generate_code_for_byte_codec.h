#ifndef GENERATE_CODE_FOR_BYTE_CODEC_H
#define GENERATE_CODE_FOR_BYTE_CODEC_H


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


void generate_byte_codec_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);
void generate_byte_codec_definition(FILE *c_stream, Tabs *tabs, Structure *structure);

void byte_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_encode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_decode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_decode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_decode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_decode_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif