#ifndef GENERATE_LIBRARY_H
#define GENERATE_LIBRARY_H

#include "c_structure_serialization/utils/program_arguments.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute);

void generate_library_source_code_for_structure(char *path_to_sources, Structure *structure);

#endif
