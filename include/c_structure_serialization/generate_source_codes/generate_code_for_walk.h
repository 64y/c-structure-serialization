#ifndef GENERATE_CODE_FOR_WALK_H
#define GENERATE_CODE_FOR_WALK_H


#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


void generate_walk_declaration(FILE *h_stream, Tabs *tabs, Structure *structure);
void generate_walk_definition(FILE *c_stream, Tabs *tabs, Structure *structure);

void walk_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);
void walk_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer);

#endif
