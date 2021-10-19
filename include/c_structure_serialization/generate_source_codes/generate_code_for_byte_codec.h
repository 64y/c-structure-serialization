#ifndef GENERATE_CODE_FOR_BYTE_CODEC_H
#define GENERATE_CODE_FOR_BYTE_CODEC_Hstructure


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


void generate_byte_codec_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);
void generate_byte_codec_definition(FILE *c_stream, Tabs *tabs, Structure *structure);

void byte_codec_out_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_codec_out_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_codec_out_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_codec_in_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_codec_in_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void byte_codec_in_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif
