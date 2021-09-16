#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "utils/basic_defines.h"
#include "utils/tabs.h"
#include "utils/array.h"
#include "utils/array_of.h"
#include "data_types/data_type.h"
#include "data_types/dimension.h"
#include "data_types/attribute.h"
#include "data_types/structure.h"
#include "data_types/structure_regular_expressions.h"


Array * directory_path_scan_for_h_files(char *directory_path) {
	Array *h_files = Array_of_string_create();
	DIR *directory;
	struct dirent *file;
	if ((directory = opendir(directory_path)) != NULL) {
		while((file = readdir(directory)) != NULL) {
			if (
				!string_equals(file->d_name, ".") &&
				!string_equals(file->d_name, "..") &&
				file->d_name[strlen(file->d_name)-1]=='h'
			) {
				Array_add(h_files, file->d_name);
			}
		}
		closedir(directory);
	}
	return h_files;
}


int main(int argc, char *argv[]) {
	char *path = string_copy(argv[1]);
	char *path_libraries = string_appends((char *[]){path, "/libraries", NULL});
	char *path_structures = string_appends((char *[]){path, "/", argv[2], NULL});

	Array *h_files = directory_path_scan_for_h_files(path_structures);
	Array_sort(h_files, array_string_cmp);
	
	Array *structures = Array_of_Structure_create();
	
	Array *structure_source_code = NULL;
	for (int h_files_i=0; h_files_i<Array_size(h_files); h_files_i++) {
		char *h_file_path = string_appends((char *[]){path_structures, "/", Array_get(h_files, h_files_i), NULL});
		char *h_file_source_code = file_read(h_file_path);
		for (char *code_line=strtok(h_file_source_code, "\n"); code_line!=NULL; code_line=strtok(NULL, "\n")) {
			if (RegularExpression_match(structureRegularExpressions->structureStart, code_line)) {
				structure_source_code = Array_of_string_create();
				Array_add(structure_source_code, code_line);
			} else if (RegularExpression_match(structureRegularExpressions->attribute, code_line)) {
				Array_add(structure_source_code, code_line);
			} else if (RegularExpression_match(structureRegularExpressions->structureEnd, code_line)) {
				Array_add(structure_source_code, code_line);
				Array_add(structures, array_Structure_arguments(h_file_path, structure_source_code));
				{
					Array_free(structure_source_code);
					structure_source_code = NULL;
				}
			}
		}
		{
			free(h_file_path);
			free(h_file_source_code);
		}
	}
	
	// TODO: 
	
	char *structures_string = Array_to_string(structures);
	puts(structures_string);
	
	{
		free(path);
		free(path_libraries);
		free(path_structures);
		
		Array_free(h_files);
		Array_free(structures);
		free(structures_string);
	}
	return 0;
}
