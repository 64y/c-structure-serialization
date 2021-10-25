#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/program_arguments.h"


ProgramArguments * ProgramArguments_create(int argc, char *argv[]) {
	ProgramArguments *programArguments = (ProgramArguments *)malloc(sizeof(ProgramArguments));
	programArguments->path_to_project = NULL;
	programArguments->path_to_sources = NULL;
	programArguments->path_to_library = NULL;
	programArguments->remove_sources = true;
	programArguments->target = Array_create_for_string();
	
	char *argument, *value;
	size_t argument_length, value_length;
	
	for (int i=1; i<argc; i++) {
		sscanf(argv[i], "%*[^=]%ln=%*s%ln", &argument_length, &value_length);
		argument = (char *)calloc(argument_length+1, sizeof(char));
		value = (char *)calloc(value_length+1, sizeof(char));
		sscanf(argv[i], "%[^=]=%s", argument, value);
		if (string_equals("path_to_project", argument)) {
			programArguments->path_to_project = string_copy(value);
		} else if (string_equals("path_to_sources", argument)) {
			programArguments->path_to_sources = string_copy(value);
		} else if (string_equals("path_to_library", argument)) {
			programArguments->path_to_library = string_copy(value);
		} else if (string_equals("remove_sources", argument)) {
			if (string_equals("no", value)) {
				programArguments->remove_sources = false;
			}
		} else if (string_equals("target", argument)) {
			if (!string_equals("every_structure", value)) {
				for (char *string=strtok(value, ","); string!=NULL; string=strtok(NULL, ",")) {
					Array_add(programArguments->target, string);
				}
			}
		} else {
			if (!string_equals("help", argument)) {
				fprintf(stderr, "Error in \'ProgramArguments_create\' - invalid argument \'%s\'!\n", argument);
			}
			ProgramArgument_print_help();
			{
				ProgramArguments_free(programArguments);
				string_free(argument);
				string_free(value);
			}
			exit(1);
		}
		{
			string_free(argument);
			string_free(value);
		}
	}
	if (programArguments->path_to_project==NULL) {
		programArguments->path_to_project = string_create(".");
	}
	if (programArguments->path_to_sources==NULL) {
		time_t time_raw = time(NULL);
		struct tm *time_info = localtime(&time_raw);
		char *abc = "0123456789ABCDEFGHIJKLMNOPQRTUVWXYZ";
		size_t abc_length = strlen(abc);
		srand((unsigned int) time(NULL));
		programArguments->path_to_sources = string_create_by_format(
			"/tmp/c_structure_serialization_"
			"%d%02d%02d_%02d%02d%02d_"
			"%c%c%c%c%c%c%c%c",
			1900+time_info->tm_year, 1+time_info->tm_mon, time_info->tm_mday,
			time_info->tm_hour, time_info->tm_min, time_info->tm_sec,
			abc[rand()%abc_length], abc[rand()%abc_length], abc[rand()%abc_length], abc[rand()%abc_length], 
			abc[rand()%abc_length], abc[rand()%abc_length], abc[rand()%abc_length], abc[rand()%abc_length]
		);
		{
			time_info = NULL;
		}
	}
	if (programArguments->path_to_library==NULL) {
		programArguments->path_to_library = string_create("my_library");
	}
	if (string_equals(programArguments->path_to_project, programArguments->path_to_sources)) {
		programArguments->remove_sources = false;
	}
	if (Array_size(programArguments->target)!=0) {
		Array_sort(programArguments->target, array_string_cmp);
	}
	return programArguments;
}

void ProgramArguments_free(ProgramArguments *programArguments) {
	if (programArguments!=NULL) {
		if (programArguments->path_to_project!=NULL) {
			free(programArguments->path_to_project);
			programArguments->path_to_project = NULL;
		}
		if (programArguments->path_to_sources!=NULL) {
			free(programArguments->path_to_sources);
			programArguments->path_to_sources = NULL;
		}
		if (programArguments->path_to_library!=NULL) {
			free(programArguments->path_to_library);
			programArguments->path_to_library = NULL;
		}
		programArguments->remove_sources = false;
		if (programArguments->target!=NULL) {
			Array_free(programArguments->target);
		}
		free(programArguments);
		programArguments = NULL;
	}
}

char * ProgramArguments_to_string(ProgramArguments *programArguments) {
	char *programArguments_target_string = Array_to_string(programArguments->target);
	char *programArguments_string = string_create_by_format(
		"ProgramArguments@%lX\n"
		"path_to_project: \'%s\';\n"
		"path_to_sources: \'%s\';\n"
		"path_to_library: \'%s\';\n"
		"remove_sources: \'%s\';\n"
		"target: \'Array@%lX\'.\n"
		"%s",
		(long)(void *)programArguments, programArguments->path_to_project, programArguments->path_to_sources, programArguments->path_to_library,  (programArguments->remove_sources)?"yes":"no", (long)(void *)programArguments->target, programArguments_target_string
	);
	{
		free(programArguments_target_string);
	}
	return programArguments_string;
}

void ProgramArgument_print_help() {
	puts(
		"Usage:\n"
		"generate_sources_and_library [argument=value ... argument=value]\n"
		"\n"
		"Arguments:\n"
		"  path_to_project\tThe path to the directory of a project, for which structures the library of codec would be generated.\n"
		"  path_to_sources\tThe path to the directory, where source codes for library would be generated. Default directory is \'/tmp/c_structure_serialization_{year}{month}{day}_{hour}{minute}{second}_{pseudo_random_char x 8}\'.\n"
		"  path_to_library\tThe path to the library file. Default file path is the program run directory and file name is \'my_library\'.\n"
		"  remove_sources\tThe flag which is determine the existence of library source codes, possible values: \"yes\"/\"no\". Default value is \"no\" - source codes would be removed.\n"
		"  target\t\tTarget structure or structures. Default value is \"every_structure\" - each structure in \'path_to_project\' would be included into library.\n"
		"\n"
		"Examples:\n"
		"  generate_sources_and_library path_to_project=example\n"
		"  generate_sources_and_library path_to_project=example path_to_library=bin/pets_library target=Pets\n"
		"  generate_sources_and_library path_to_project=example path_to_library=bin/matrix_library target=Matrix3D,Arrays,String\n"
		"\n"
		"Full documentation <https://github.com/64y/c-structure-serialization>.\n"
	);
}
