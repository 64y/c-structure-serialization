#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/files.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"
#include "c_structure_serialization/generate_source_codes/generate_to_string_method.h"
#include "c_structure_serialization/generate_source_codes/generate_json_codec.h"
#include "c_structure_serialization/generate_source_codes/generate_byte_codec.h"


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
	char *path_libraries = string_appends(path, "/libraries", NO_MORE_STRINGS);
	char *path_structures = string_appends(path, "/", structures_path, NO_MORE_STRINGS);

	Array *h_files = directory_path_scan_for_h_files(path_structures);
	Array_sort(h_files, array_string_cmp);
	
	Array *structures = Array_create_for_Structure();
	
	Array *structure_source_code = NULL;
	for (int h_files_i=0; h_files_i<Array_size(h_files); h_files_i++) {
		char *h_file_path = string_appends(path_structures, "/", Array_get(h_files, h_files_i), NO_MORE_STRINGS);
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
			string_free(h_file_path);
			string_free(h_file_source_code);
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
		string_free(path);
		string_free(path_libraries);
		string_free(path_structures);
		Array_free(h_files);
		Array_free(structures);
	}
}

void generate_library_for_structure(char *project_path, Structure *structure) {
	char *path_libraries = string_appends(project_path, "/libraries", NO_MORE_STRINGS);
	mkdir(path_libraries, 0777);
	char *structure_library_h_file_name = string_appends(path_libraries, "/", structure->name_lower, "_library.h", NO_MORE_STRINGS);
	char *structure_library_c_file_name = string_appends(path_libraries, "/", structure->name_lower, "_library.c", NO_MORE_STRINGS);
	char *code_h;
	{
		size_t generate_code_size = 3;
		char * (*generate_code[]) (Structure *structure) = {
			generate_to_string_method_declaration,
			generate_json_codec_declaration,
			generate_byte_codec_declaration
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
		size_t generate_code_size = 3;
		char * (*generate_code[]) (Structure *structure) = {
			generate_to_string_method_definition,
			generate_json_codec_definition,
			generate_byte_codec_definition
		};
		
		size_t code_c_length;
		FILE *code_c_stream = open_memstream(&code_c, &code_c_length);
		fprintf(code_c_stream, "#include \"includes.h\"\n");
		for (int i=0; i<generate_code_size; i++) {
			char *code = generate_code[i](structure);
			fprintf(code_c_stream, "\n\n%s", code);
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
	
	char *structure_name_h_path = string_appends(project_path, "/_structure/structure_name.h", NO_MORE_STRINGS);
	char *structure_name_h_format = file_read(structure_name_h_path);
	char *structure_name_h_source_code = string_create_by_format(structure_name_h_format, names);
	file_write(structure_name_h_path, structure_name_h_source_code);
	
	char *structure_name_c_path = string_appends(project_path, "/_structure/structure_name.c", NO_MORE_STRINGS);
	char *structure_name_c_format = file_read(structure_name_c_path);
	char *structure_name_c_source_code = string_create_by_format(structure_name_c_format, structures_size, names_strings);
	file_write(structure_name_c_path, structure_name_c_source_code);
	{
		string_free(names);
		string_free(names_strings);
		string_free(structure_name_h_path);
		string_free(structure_name_h_format);
		string_free(structure_name_h_source_code);
		string_free(structure_name_c_path);
		string_free(structure_name_c_format);
		string_free(structure_name_c_source_code);
	}
}

void generate_structure_methods_file(char *project_path, Array *structures) {
	size_t structures_size = Array_size(structures);
	size_t methods_names_size = 5;
	char *methods_names[] = {
		"_to_string_process",
		"_json_encode_process",
		"_json_decode_process",
		"_byte_encode_process",
		"_byte_decode_process"
	};
	char *methods;
	{
		size_t methods_length;
		FILE *methods_stream = open_memstream(&methods, &methods_length);
		fprintf(methods_stream, "{\n");
		for (int i=0; i<structures_size; i++) {
			char *structure_name = ((Structure *) Array_get(structures, i))->name;
			fprintf(methods_stream, "\t{\n");
			for (int j=0; j<methods_names_size; j++) {
				fprintf(methods_stream, "\t\t%s%s%s", structure_name, methods_names[j], (j<methods_names_size-1)?",\n":"\n");
			}
			fprintf(methods_stream, "\t}%s\n", (i<structures_size-1)?",":"");
		}
		fprintf(methods_stream, "}\n");
		{
			fclose(methods_stream);
		}
	}
	
	char *structure_methods_c_path = string_appends(project_path, "/_structure/structure_methods.c", NO_MORE_STRINGS);
	char *structure_methods_c_format = file_read(structure_methods_c_path);
	char *structure_methods_c_source_code = string_create_by_format(structure_methods_c_format, methods);
	file_write(structure_methods_c_path, structure_methods_c_source_code);
	{
		string_free(methods);
		string_free(structure_methods_c_path);
		string_free(structure_methods_c_format);
		string_free(structure_methods_c_source_code);
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
			char *include_structure = string_create_by_format("#include \"%s/%s\"", structures_path, structure->file_path);
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
	char *structure_includes_h_path = string_appends(project_path, "/includes.h", NO_MORE_STRINGS);
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


