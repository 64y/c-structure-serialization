#ifndef GENERATE_CODE_FOR_TO_STRING_H
#define GENERATE_CODE_FOR_TO_STRING_H


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


void generate_to_string_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);
void generate_to_string_definition(FILE *c_stream, Tabs *tabs, Structure *structure);

void to_string_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void to_string_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif
