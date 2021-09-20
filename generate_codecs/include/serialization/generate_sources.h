#ifndef GENERATE_SOURCES_H
#define GENERATE_SOURCES_H

#include "utils/basic_defines.h"
#include "utils/tabs.h"
#include "data_types/attribute.h"
#include "data_types/structure.h"


void generate_sources(char *project_path, char *structures_path);

void generate_structure_library_and_dependencies(char *project_path, char *structures_path, Structure *structure);

char * generate_pass_method_declaration(Structure *structure);
char * generate_pass_method_definition(Structure *structure);

char * generate_attribute_pointer(Structure *structure, Attribute *attribute);
char * generate_attribute_with_loop(Tabs *tabs, Structure *structure, Attribute *attribute, Boolean slash_n);

#endif
