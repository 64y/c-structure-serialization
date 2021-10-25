/** @file
@brief A declaration of ProgramArguments structure and its methods. */
#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H


#include <stdbool.h>

#include "c_structure_serialization/utils/array.h"


/// ProgramArguments structure contains all necessary for further work arguments.
typedef struct ProgramArguments {
	char *path_to_project; ///< Path to project, this directory will be scaned for *.h files and structures inside it.
	char *path_to_sources; ///< Path to source code, this directory will be used to generate source codes for libraries.
	char *path_to_library; ///< Path to library to be generated where.
	bool remove_sources; ///< Flag to remove source codes after the library would be generated.
	Array *target; ///< An Array of structure names to be in library.
} ProgramArguments;

/** @brief Creates ProgramArguments.
@details Method parses program console arguments and creates an instance of ProgramArguments structure or print help note if there are problems in arguments.
@param argc Number of arguments in argument array;
@param argv Argument array.
@return Created ProgramArguments. */
ProgramArguments * ProgramArguments_create(int argc, char *argv[]);

/** @brief Frees memory of ProgramArguments.
@details Methods frees string paths, frees Array target and frees an instance of structure Array and assigns a NULL value.
@param programArguments A pointer to instance of structure ProgramArguements.*/
void ProgramArguments_free(ProgramArguments *programArguments);

/** @brief Gets string of ProgramArguments.
@details Method creates a string representation for an instance of structure ProgramArguments.
@param programArguments A pointer to instance of structure ProgramArguments.
@return A string representation of ProgramArguments. */
char * ProgramArguments_to_string(ProgramArguments *programArguments);


/** @brief Print help.
@details Method prints help note into console */
void ProgramArgument_print_help();

#endif
