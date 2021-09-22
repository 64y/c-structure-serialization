#ifndef GENERATE_LIBRARIES_H
#define GENERATE_LIBRARIES_H


#include "c_structure_serialization/data_types/structure.h"

// TODO: change string_to_upper to string_to_upper_safe

void generate_sources(char *project_path, char *structures_path);

void generate_library_for_structure(char *project_path, Structure *structure);

#endif
