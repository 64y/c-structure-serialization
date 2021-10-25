/** @file
@brief A method to generate source codes and library. */
#ifndef GENERATE_SOURCES_H
#define GENERATE_SOURCES_H


#include "c_structure_serialization/utils/program_arguments.h"


/** @brief Method generates source codes and compiles them into the dynamic library file, based on program arguments.
@param programArguments A pointer for an instance of structure ProgramArguments. */
void generate_source_codes_and_library(ProgramArguments *programArguments);

#endif
