#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/files.h"
#include "c_structure_serialization/utils/program_arguments.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"
#include "c_structure_serialization/generate_source_codes/generate_sources.h"
#include "c_structure_serialization/generate_source_codes/generate_library.h"


void generate_file_includes(char *path_to_sources, Array *structures);
void generate_file_structure_info(char *path_to_sources, Array *structures);

void generate_source_codes_and_library(ProgramArguments *programArguments) {
	Array *structures = Array_create_for_Structure();
	{
		size_t path_to_project_length = strlen(programArguments->path_to_project);
		Array *h_files = directory_path_scan_for_h_files(programArguments->path_to_project);
		for (int h_files_i=0; h_files_i<Array_size(h_files); h_files_i++) {
			char *h_file_path = Array_get(h_files, h_files_i);
			char *h_file_source_code = file_read(h_file_path);
			for (char *code_line=strtok(h_file_source_code, "\n"); code_line!=NULL; code_line=strtok(NULL, "\n")) {
				if (RegularExpression_match(structureRegularExpressions->structureStart, code_line)) {
					char *file_path = h_file_path+path_to_project_length+1;
					Array *structure_source_code = Array_create_for_string();
					Array_add(structure_source_code, code_line);
					for (code_line=strtok(NULL, "\n"); code_line!=NULL; code_line=strtok(NULL, "\n")) {
						if (RegularExpression_match(structureRegularExpressions->attribute, code_line)) {
							Array_add(structure_source_code, code_line);
						}
						if (RegularExpression_match(structureRegularExpressions->structureEnd, code_line)) {
							Array_add(structure_source_code, code_line);
							break;
						}
					}
					Array_add(structures, file_path, structure_source_code);
					{
						file_path = NULL;
						Array_free(structure_source_code);
					}
				}
			}
			{
				h_file_path = NULL;
				string_free(h_file_source_code);
			}
		}
		{
			Array_free(h_files);
		}
	}
	if (Array_size(programArguments->target)!=0) {
		Array *structures_all = structures;
		structures = Array_create_for_Structure();
		for (int target_i=0; target_i<Array_size(programArguments->target); target_i++) {
			for (int structures_all_i=0; structures_all_i<Array_size(structures_all); structures_all_i++) {
				if (
					Array_get(structures_all, structures_all_i)!=NULL &&
					string_equals(
						(char *) Array_get(programArguments->target, target_i),
						((Structure *) Array_get(structures_all, structures_all_i))->name
					)
				) {
					Structure *structure = (Structure *) Array_get(structures_all, structures_all_i);
					structures_all->elements[structures_all_i] = NULL;
					Array_put(structures, structure);
					for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
						if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_POINTER || attribute->type==STRUCTURE_ARRAY || attribute->type==STRUCTURE_POINTER_ARRAY) {
							bool presents = false;
							for (int target_j=0; target_j<Array_size(programArguments->target); target_j++) {
								if (string_equals((char *) Array_get(programArguments->target, target_j), attribute->data_type)) {
									presents = true;
									break;
								}
							}
							if (!presents) {
								Array_add(programArguments->target, attribute->data_type);
							}
						}
					}
				}
			}
		}
		{
			Array_free(structures_all);
		}
	}
	
	char *command_to_copy;
	{
		size_t command_to_copy_length;
		FILE *command_to_copy_stream = open_memstream(&command_to_copy, &command_to_copy_length);
		if (!string_equals(programArguments->path_to_project, programArguments->path_to_sources)) {
			fprintf(command_to_copy_stream, "mkdir -p %s\n", programArguments->path_to_sources);
		}
		fprintf(command_to_copy_stream, "cp $C_STRUCTURE_SERIALIZATION_HOME/res/* %s -r", programArguments->path_to_sources);
		if (!string_equals(programArguments->path_to_project, programArguments->path_to_sources)) {
			for (int structures_i=0; structures_i<Array_size(structures); structures_i++) {
				Structure *structure = (Structure *) Array_get(structures, structures_i);
				fflush(command_to_copy_stream);
				if (strstr(command_to_copy, structure->file_path)!=NULL) {
					continue;
				}
				fprintf(
					command_to_copy_stream,
					"\nmkdir -p $(dirname %2$s/%3$s)\n"
					"cp $(echo \"%1$s/%3$s\" | sed \'s/.$/*/\') $(dirname %2$s/%3$s) -r",
					programArguments->path_to_project, programArguments->path_to_sources, structure->file_path);
			}
		}
		{
			fclose(command_to_copy_stream);
		}
	}
	system(command_to_copy);
	
	generate_file_includes(programArguments->path_to_sources, structures);
	generate_file_structure_info(programArguments->path_to_sources, structures);
	
	for (int structures_i=0; structures_i<Array_size(structures); structures_i++) {
		Structure *structure = (Structure *) Array_get(structures, structures_i);
		generate_library_source_codes_for_structure(programArguments->path_to_sources, structure);
	}
	
	char *command_to_create_library = NULL;/* = string_create_by_format(
		"mkdir -p $(dirname %1$s)\n"
		"gcc -shared -nostartfiles -fPIC -o %1$s -I %2$s $(find %2$s -type f -name \"*.c\")",
		programArguments->path_to_library, programArguments->path_to_sources
	);
	system(command_to_create_library);
	*/
	{
		Array_free(structures);
		string_free(command_to_copy);
		string_free(command_to_create_library);
	}
}


void generate_file_includes(char *path_to_sources, Array *structures) {
	size_t structures_size = Array_size(structures);
	char *include_structures, *include_libraries;
	{
		size_t include_structures_length, include_libraries_strings_length;
		FILE *include_structures_stream = open_memstream(&include_structures, &include_structures_length), *include_libraries_stream = open_memstream(&include_libraries, &include_libraries_strings_length);
		for (int i=0; i<structures_size; i++) {
			Structure *structure = (Structure *) Array_get(structures, i);
			char *include_structure = string_create_by_format("#include \"%s\"", structure->file_path);
			fflush(include_structures_stream);
			if (strstr(include_structures, include_structure)==NULL) {
				fprintf(include_structures_stream, "%s\n", include_structure);
			}
			fprintf(include_libraries_stream, "#include \"libraries/%s_library.h\"\n", structure->name_lower);
			{
				string_free(include_structure);
			}
		}
		{
			fclose(include_structures_stream);
			fclose(include_libraries_stream);
		}
	}
	char *structure_includes_h_path = string_appends(path_to_sources, "/includes.h", NO_MORE_STRINGS);
	char *structure_includes_h_format = file_read(structure_includes_h_path);
	char *structure_includes_h_source_code = string_create_by_format(structure_includes_h_format, include_structures, include_libraries);
	file_write(structure_includes_h_path, structure_includes_h_source_code);
	{
		string_free(include_structures);
		string_free(include_libraries);
		
		string_free(structure_includes_h_path);
		string_free(structure_includes_h_format);
		string_free(structure_includes_h_source_code);
	}
}

void generate_file_structure_info(char *path_to_sources, Array *structures) {
	size_t structures_methods_names_size = 5;
	char *structures_methods_names[] = {
		"to_string_process",
		"json_encode_process",
		"json_decode_process",
		"byte_encode_process",
		"byte_decode_process"
	};
	size_t structures_size = Array_size(structures);
	char *enum_structure_name, *enum_structure_name_string, *structures_methods;
	{
		size_t enum_structure_name_length;
		FILE *enum_structure_name_stream = open_memstream(&enum_structure_name, &enum_structure_name_length);
		size_t enum_structure_name_string_length;
		FILE *enum_structure_name_string_stream = open_memstream(&enum_structure_name_string, &enum_structure_name_string_length);
		for (int i=0; i<structures_size; i++) {
			Structure *structure = ((Structure *) Array_get(structures, i));
			fprintf(enum_structure_name_stream, "%s%s", structure->name_upper, (i<structures_size-1)?",\n\t":"");
			fprintf(enum_structure_name_string_stream, "\"%s\"%s", structure->name, (i<structures_size-1)?",\n\t":"");
		}
		{
			fclose(enum_structure_name_stream);
			fclose(enum_structure_name_string_stream);
		}
		size_t structures_methods_length;
		FILE *structures_methods_stream = open_memstream(&structures_methods, &structures_methods_length);
		fprintf(structures_methods_stream, "{\n");
		for (int i=0; i<structures_methods_names_size; i++) {
			fprintf(structures_methods_stream, "\t{\n");
			for (int j=0; j<structures_size; j++) {
				Structure *structure = ((Structure *) Array_get(structures, j));
				fprintf(structures_methods_stream, "\t\t%s_%s%s", structure->name, structures_methods_names[i], (j<structures_methods_names_size-1)?",\n":"\n");
			}
			fprintf(structures_methods_stream, "\t}%s\n", (i<structures_size-1)?",":""); 
		}
		fprintf(structures_methods_stream, "}");
		{
			fclose(structures_methods_stream);
		}
	}
	char *structure_info_h_path = string_appends(path_to_sources, "/_structure/structure_info.h", NO_MORE_STRINGS);
	char *structure_info_h_format = file_read(structure_info_h_path);
	char *structure_info_h_source_code = string_create_by_format(structure_info_h_format, enum_structure_name, structures_size);
	file_write(structure_info_h_path, structure_info_h_source_code);
	char *structure_info_c_path = string_appends(path_to_sources, "/_structure/structure_info.c", NO_MORE_STRINGS);
	char *structure_info_c_format = file_read(structure_info_c_path);
	char *structure_info_c_source_code = string_create_by_format(structure_info_c_format, structures_size, enum_structure_name_string, structures_size, structures_methods);
	file_write(structure_info_c_path, structure_info_c_source_code);
	{
		string_free(enum_structure_name);
		string_free(enum_structure_name_string);
		string_free(structures_methods);
		string_free(structure_info_h_path);
		string_free(structure_info_h_format);
		string_free(structure_info_h_source_code);
		string_free(structure_info_c_path);
		string_free(structure_info_c_format);
		string_free(structure_info_c_source_code);
	}
}
