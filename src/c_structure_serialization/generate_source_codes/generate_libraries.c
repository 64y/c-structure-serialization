#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/files.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"
#include "c_structure_serialization/generate_source_codes/generate_to_string_method.h"
#include "c_structure_serialization/generate_source_codes/generate_json_codec.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute) {
	char *pointer;
	{
		size_t pointer_length;
		FILE *pointer_stream = open_memstream(&pointer, &pointer_length);
		if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
			fprintf(pointer_stream, "&");
		}
		fprintf(pointer_stream, "%s->%s", structure->shortcut, attribute->name);
		fclose(pointer_stream);
	}
	return pointer;
}


void generate_structure_name_file(char *project_path, Array *structures);
void generate_structure_methods_file(char *project_path, Array *structures);
void generate_includes_file(char *project_path, char *structures_path, Array *structures);


void generate_sources(char *project_path, char *structures_path) {
	char *path = string_copy(project_path);
	char *path_libraries = string_appends((char *[]){path, "/libraries", NULL});
	char *path_structures = string_appends((char *[]){path, "/", structures_path, NULL});

	Array *h_files = directory_path_scan_for_h_files(path_structures);
	Array_sort(h_files, array_string_cmp);
	
	Array *structures = Array_create_for_Structure();
	
	Array *structure_source_code = NULL;
	for (int h_files_i=0; h_files_i<Array_size(h_files); h_files_i++) {
		char *h_file_path = string_appends((char *[]){path_structures, "/", Array_get(h_files, h_files_i), NULL});
		char *h_file_source_code = file_read(h_file_path);
		for (char *code_line=strtok(h_file_source_code, "\n"); code_line!=NULL; code_line=strtok(NULL, "\n")) {
			if (RegularExpression_match(structureRegularExpressions->structureStart, code_line)) {
				structure_source_code = Array_create_for_string();
				Array_add(structure_source_code, code_line);
			} else if (RegularExpression_match(structureRegularExpressions->attribute, code_line)) {
				Array_add(structure_source_code, code_line);
			} else if (RegularExpression_match(structureRegularExpressions->structureEnd, code_line)) {
				Array_add(structure_source_code, code_line);
				Array_add(structures, array_Structure_create_pack_arguments(Array_get(h_files, h_files_i), structure_source_code));
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
	// TODO: edit ^ to scan directories
	generate_structure_name_file(project_path, structures);
	generate_structure_methods_file(project_path, structures);
	generate_includes_file(project_path, structures_path, structures);
	for (int i=0; i<Array_size(structures); i++) {
		generate_library_for_structure(project_path, (Structure *) Array_get(structures, i));
	}
	{
		free(path);
		free(path_libraries);
		free(path_structures);
		Array_free(h_files);
		Array_free(structures);
	}
}

void generate_library_for_structure(char *project_path, Structure *structure) {
	char *path_libraries = string_appends((char *[]){project_path, "/libraries", NULL});
	mkdir(path_libraries, 0777);
	char *structure_library_h_file_name = string_appends((char *[]){path_libraries, "/", structure->name_lower, "_library.h", NULL});
	char *structure_library_c_file_name = string_appends((char *[]){path_libraries, "/", structure->name_lower, "_library.c", NULL});
	char *code_h;
	{
		size_t generate_code_size = 2;
		char * (*generate_code[]) (Structure *structure) = {
			generate_to_string_method_declaration,
			generate_json_codec_declaration
		};
		
		size_t code_h_length;
		FILE *code_h_stream = open_memstream(&code_h, &code_h_length);
		fprintf(code_h_stream, "#ifndef %s_LIBRARY_H\n", structure->name_upper);
		fprintf(code_h_stream, "#define %s_LIBRARY_H\n", structure->name_upper);
		fprintf(code_h_stream, "\n");
		fprintf(code_h_stream, "#include \"includes.h\"\n");
		fprintf(code_h_stream, "\n");
		for (int i=0; i<generate_code_size; i++) {
			char *code = generate_code[i](structure);
			fprintf(code_h_stream, "%s\n\n", code);
			free(code);
		}
		fprintf(code_h_stream, "#endif");
		{
			fclose(code_h_stream);
		}
	}
	file_write(structure_library_h_file_name, code_h);
	char *code_c;
	{
		size_t generate_code_size = 2;
		char * (*generate_code[]) (Structure *structure) = {
			generate_to_string_method_definition,
			generate_json_codec_definition
		};
		
		size_t code_c_length;
		FILE *code_c_stream = open_memstream(&code_c, &code_c_length);
		fprintf(code_c_stream, "#include \"includes.h\"\n");
		fprintf(code_c_stream, "\n");
		for (int i=0; i<generate_code_size; i++) {
			char *code = generate_code[i](structure);
			fprintf(code_c_stream, "%s\n\n", code);
			free(code);
		}
		{
			fclose(code_c_stream);
		}
	}
	file_write(structure_library_c_file_name, code_c);
	{
		free(path_libraries);
		free(structure_library_h_file_name);
		free(structure_library_c_file_name);
		free(code_h);
		free(code_c);
	}
}


void generate_structure_name_file(char *project_path, Array *structures) {
	size_t structures_size = Array_size(structures);
	char *names, *names_strings;
	{
		size_t names_length, names_strings_length;
		FILE *names_stream = open_memstream(&names, &names_length), *names_strings_stream = open_memstream(&names_strings, &names_strings_length);
		for (int i=0; i<structures_size; i++) {
			fprintf(names_stream, "%s%s", ((Structure *) Array_get(structures, i))->name_upper, (i<structures_size-1)?",\n\t":"");
			fprintf(names_strings_stream, "\"%s\"%s", ((Structure *) Array_get(structures, i))->name, (i<structures_size-1)?",\n\t":"");
		}
		{
			fclose(names_stream);
			fclose(names_strings_stream);
		}
	}
	
	char *structure_name_h_path = string_appends((char *[]){project_path, "/_structure/structure_name.h", NULL});
	char *structure_name_h_format = file_read(structure_name_h_path);
	char *structure_name_h_source_code;
	{
		size_t structure_name_h_source_code_length;
		FILE *structure_name_h_source_code_stream = open_memstream(&structure_name_h_source_code, &structure_name_h_source_code_length);
		fprintf(structure_name_h_source_code_stream, structure_name_h_format, names);
		{
			fclose(structure_name_h_source_code_stream);
		}
	}
	file_write(structure_name_h_path, structure_name_h_source_code);
	
	char *structure_name_c_path = string_appends((char *[]){project_path, "/_structure/structure_name.c", NULL});
	char *structure_name_c_format = file_read(structure_name_c_path);
	char *structure_name_c_source_code;
	{
		size_t structure_name_c_source_code_length;
		FILE *structure_name_c_source_code_stream = open_memstream(&structure_name_c_source_code, &structure_name_c_source_code_length);
		fprintf(structure_name_c_source_code_stream, structure_name_c_format, structures_size, names_strings);
		{
			fclose(structure_name_c_source_code_stream);
		}
	}
	file_write(structure_name_c_path, structure_name_c_source_code);
	{
		free(names);
		free(names_strings);
		free(structure_name_h_path);
		free(structure_name_h_format);
		free(structure_name_h_source_code);
		free(structure_name_c_path);
		free(structure_name_c_format);
		free(structure_name_c_source_code);
	}
}

void generate_structure_methods_file(char *project_path, Array *structures) {
	size_t structures_size = Array_size(structures);
	char *to_string_methods, *json_encode_methods, *json_decode_methods;
	{
		size_t to_string_methods_length, json_encode_methods_length, json_decode_methods_length;
		FILE *to_string_methods_stream = open_memstream(&to_string_methods, &to_string_methods_length), *json_encode_methods_stream = open_memstream(&json_encode_methods, &json_encode_methods_length), *json_decode_methods_stream = open_memstream(&json_decode_methods, &json_decode_methods_length);
		for (int i=0; i<structures_size; i++) {
			char *structure_name = ((Structure *) Array_get(structures, i))->name;
			fprintf(to_string_methods_stream, "%s_to_string_process%s", structure_name, (i<structures_size-1)?",\n\t":"");
			fprintf(json_encode_methods_stream, "%s_json_encode_process%s", structure_name, (i<structures_size-1)?",\n\t":"");
			fprintf(json_decode_methods_stream, "%s_json_decode_process%s", structure_name, (i<structures_size-1)?",\n\t":"");
		}
		{
			fclose(to_string_methods_stream);
			fclose(json_encode_methods_stream);
			fclose(json_decode_methods_stream);
		}
	}
	
	char *structure_methods_c_path = string_appends((char *[]){project_path, "/_structure/structure_methods.c", NULL});
	char *structure_methods_c_format = file_read(structure_methods_c_path);
	char *structure_methods_c_source_code;
	{
		size_t structure_methods_c_source_code_length;
		FILE *structure_methods_c_source_code_stream = open_memstream(&structure_methods_c_source_code, &structure_methods_c_source_code_length);
		fprintf(structure_methods_c_source_code_stream, structure_methods_c_format, to_string_methods, json_encode_methods, json_decode_methods);
		{
			fclose(structure_methods_c_source_code_stream);
		}
	}
	file_write(structure_methods_c_path, structure_methods_c_source_code);
	{
		free(to_string_methods);
		free(json_encode_methods);
		free(json_decode_methods);
		free(structure_methods_c_path);
		free(structure_methods_c_format);
		free(structure_methods_c_source_code);
	}
}

void generate_includes_file(char *project_path, char *structures_path, Array *structures) {
	size_t structures_size = Array_size(structures);
	char *include_structures, *include_libraries;
	{
		size_t include_structures_length, include_libraries_strings_length;
		FILE *include_structures_stream = open_memstream(&include_structures, &include_structures_length), *include_libraries_stream = open_memstream(&include_libraries, &include_libraries_strings_length);
		for (int i=0; i<structures_size; i++) {
			Structure *structure = (Structure *) Array_get(structures, i);
			char *include_structure;
			{
				size_t include_structure_length;
				FILE *include_structure_stream = open_memstream(&include_structure, &include_structure_length);
				fprintf(include_structure_stream, "#include \"%s/%s\"", structures_path, structure->file_path);
				{
					fclose(include_structure_stream);
				}
			}
			fflush(include_structures_stream);
			if (strstr(include_structures, include_structure)==NULL) {
				fprintf(include_structures_stream, "%s\n", include_structure);
			}
			fprintf(include_libraries_stream, "#include \"libraries/%s_library.h\"\n", structure->name_lower);
			{
				free(include_structure);
			}
		}
		{
			fclose(include_structures_stream);
			fclose(include_libraries_stream);
		}
	}
	char *structure_includes_h_path = string_appends((char *[]){project_path, "/includes.h", NULL});
	char *structure_includes_h_format = file_read(structure_includes_h_path);
	char *structure_includes_h_source_code;
	{
		size_t structure_includes_h_source_code_length;
		FILE *structure_includes_h_source_code_stream = open_memstream(&structure_includes_h_source_code, &structure_includes_h_source_code_length);
		fprintf(structure_includes_h_source_code_stream, structure_includes_h_format, include_structures, include_libraries);
		{
			fclose(structure_includes_h_source_code_stream);
		}
	}
	file_write(structure_includes_h_path, structure_includes_h_source_code);
	{
		free(include_structures);
		free(include_libraries);
		
		free(structure_includes_h_path);
		free(structure_includes_h_format);
		free(structure_includes_h_source_code);
	}
}


