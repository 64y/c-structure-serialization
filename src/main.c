#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"


char *md5_of_files_in_structures_path(char *full_path_to_structures) {
	char *command;
	{
		size_t command_length;
		FILE *command_stream = open_memstream(&command, &command_length);
		fprintf(command_stream, "md5sum %s/* | awk '{ print $1 }' | md5sum | awk '{ print $1 }'", full_path_to_structures);
		{
			fclose(command_stream);
		}
	}
	char *md5;
	{
		size_t md5_length = 32;
		md5 = (char *)calloc(md5_length+1, sizeof(char));
		FILE *md5_stream = popen(command, "r");
		fread(md5, sizeof(char), md5_length, md5_stream);
		{
			fclose(md5_stream);
		}
	}
	{
		free(command);
	}
	return md5;
}

int main(int argc, char *argv[]) {
	char *path_to_project;
	char *path_to_structures;
	char *path_to_created_library;
	
	if (argc == 3) {
		path_to_project = string_copy("");
		path_to_structures = string_copy(argv[1]);
		path_to_created_library = string_copy(argv[2]);
	} else if (argc == 4) {
		path_to_project = string_copy(argv[1]);
		path_to_structures = string_copy(argv[2]);
		path_to_created_library = string_copy(argv[3]);
	} else {
		fprintf(
			stderr,
			"There should be two or three arguments:\n"
			"* [two] * if this program exe from project\'s directory:\n"
			"generate_library \"path_to_\" \"path_to_created_library\"\n"
			"* [tree] * if this program exe outside project\'s directory:\n"
			"generate_library \"path_to_project_directory\" \"path_to_structures_directory_inside_project_directory\" \"path_to_created_library\"\n"
		);
		return -1;
	}
	
	char *full_path_to_structures = (string_equals(path_to_project, "")) ? string_copy(path_to_structures) : string_appends((char *[]) {path_to_project, "/", path_to_structures, NULL});
	char *md5_of_files_in_path_to_structures = md5_of_files_in_structures_path(full_path_to_structures);
	char *path_to_temporary_sources = string_appends((char *[]){"/tmp/c_structure_serialization_", md5_of_files_in_path_to_structures, NULL});
	
	char *command_to_copy;
	{
		size_t command_to_copy_length;
		FILE *command_to_copy_stream = open_memstream(&command_to_copy, &command_to_copy_length);
		fprintf(
			command_to_copy_stream,
			"mkdir %s\n"
			"cp $C_STRUCTURE_SERIALIZATION_HOME/res/* %s -r\n"
			"cp %s %s -r",
			path_to_temporary_sources,
			path_to_temporary_sources,
			full_path_to_structures, path_to_temporary_sources
		);
		{
			fclose(command_to_copy_stream);
		}
	}
	system(command_to_copy);
	
	generate_sources(path_to_temporary_sources, path_to_structures);
	
	char *command_to_create_library;
	{
		size_t command_to_create_library_length;
		FILE *command_to_create_library_stream = open_memstream(&command_to_create_library, &command_to_create_library_length);
		fprintf(
			command_to_create_library_stream,
			"gcc "
			"-shared -nostartfiles -fPIC "
			"-o %s "
			"-I %s "
			"$(find %s -type f -name \"*.c\")\n"
			"rm %s -rf",
			path_to_created_library,
			path_to_temporary_sources, path_to_temporary_sources, path_to_temporary_sources
		);
		{
			fclose(command_to_create_library_stream);
		}
	}
	system(command_to_create_library);
	
	{
		free(path_to_project);
		free(path_to_structures);
		free(path_to_created_library);
		free(full_path_to_structures);
		free(md5_of_files_in_path_to_structures);
		free(path_to_temporary_sources);
		free(command_to_copy);
		free(command_to_create_library);
	}
	return 0;
}
