#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H


#include <stdbool.h>

#include "c_structure_serialization/utils/array.h"


typedef struct ProgramArguments {
	char *path_to_project;
	char *path_to_sources;
	char *path_to_library;
	bool remove_sources;
	Array *target;
} ProgramArguments;

ProgramArguments * ProgramArguments_create(int argc, char *argv[]);
void ProgramArguments_free(ProgramArguments *programArguments);
char * ProgramArguments_to_string(ProgramArguments *programArguments);

void ProgramArgument_print_help();

#endif
