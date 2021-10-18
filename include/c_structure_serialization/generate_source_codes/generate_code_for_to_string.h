#ifndef GENERATE_CODE_FOR_TO_STRING_H
#define GENERATE_CODE_FOR_TO_STRING_H


#include "c_structure_serialization/data_types/structure.h"


char * generate_to_string_method_declaration(Structure *structure);
char * generate_to_string_method_definition(Structure *structure);

#endif
