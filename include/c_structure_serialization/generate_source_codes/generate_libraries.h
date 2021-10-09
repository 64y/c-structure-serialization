#ifndef GENERATE_LIBRARIES_H
#define GENERATE_LIBRARIES_H


#include "c_structure_serialization/data_types/structure.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute);

void generate_sources(char *project_path, char *structures_path);

void generate_library_for_structure(char *project_path, Structure *structure);

#endif
