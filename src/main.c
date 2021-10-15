#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"


// compile total heap usage: 8,198 allocs, 8,198 frees, 10,667,199 bytes allocated
// example total heap usage: 21,275 allocs, 21,275 frees, 18,621,984 bytes allocated


char *md5_of_files_in_structures_path(char *full_path_to_structures) {
	char *command = string_create_by_format(
		"echo -n `md5sum %s/* | awk \'{ print $1 }\' | md5sum | awk \'{ print $1 }\'`;echo -n \"_\"; echo -n `date +%%F_%%T`",
		full_path_to_structures
	);
	char *md5;
	{
		size_t md5_length = 32+20;
		md5 = (char *)calloc(md5_length+1, sizeof(char));
		FILE *md5_stream = popen(command, "r");
		fread(md5, sizeof(char), md5_length, md5_stream);
		{
			pclose(md5_stream);
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
	
	char *full_path_to_structures = (string_equals(path_to_project, "")) ? string_copy(path_to_structures) : string_appends(path_to_project, "/", path_to_structures, NO_MORE_STRINGS);
	char *md5_of_files_in_path_to_structures = md5_of_files_in_structures_path(full_path_to_structures);
	char *path_to_temporary_sources = string_appends("/tmp/c_structure_serialization_", md5_of_files_in_path_to_structures, NO_MORE_STRINGS);
	
	char *command_to_copy = string_create_by_format("mkdir %1$s\ncp $C_STRUCTURE_SERIALIZATION_HOME/res/* %1$s -r\ncp %2$s %1$s -r", path_to_temporary_sources, full_path_to_structures);
	system(command_to_copy);
	
	generate_sources(path_to_temporary_sources, path_to_structures);
	
	char *command_to_create_library = string_create_by_format("gcc shared -nostartfiles -fPIC o %1$s I %2$s find %2$s -type f -name \"*.c\")\nrm %2$s -rf", path_to_created_library, path_to_temporary_sources);
	system(command_to_create_library);
	
	{
		string_free(path_to_project);
		string_free(path_to_structures);
		string_free(path_to_created_library);
		string_free(full_path_to_structures);
		string_free(md5_of_files_in_path_to_structures);
		string_free(path_to_temporary_sources);
		string_free(command_to_copy);
		string_free(command_to_create_library);
	}
	return 0;
}
