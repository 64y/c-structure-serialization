/** @file
@brief A method to generate source codes (*.h file and *.c file) for Structure. */
#ifndef GENERATE_LIBRARY_H
#define GENERATE_LIBRARY_H


#include "c_structure_serialization/utils/program_arguments.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"


/** @brief Generates an attribute pointer: {Structure's shortcut}->{Attribute's name}{indexes}.
@param structure A pointer for an instance of structure Structure;
@param attribute A pointer for an instance of structure Attribute;
@param indexes An indexes for attribute, NULL if attribute is a variable without dimensions.
@return Generated string representation of pointer for Attribute. */
char * generate_attribute_pointer(Structure *structure, Attribute *attribute, char *indexes);

/** @brief Generates source codes for Structure.
@param path_to_sources A path of sources directory;
@param structure A pointer for an instance of structure Structure. */
void generate_library_source_codes_for_structure(char *path_to_sources, Structure *structure);

#endif
