#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/basic_defines.h"
#include "utils/array.h"
#include "utils/array_of.h"
#include "data_types/data_type.h"
#include "data_types/dimension.h"
#include "data_types/attribute.h"
#include "data_types/structure.h"
#include "data_types/structure_regular_expressions.h"

#include "serialization/generate_sources.h"
#include "serialization/generate_to_string_method.h"
#include "serialization/generate_json_codec.h"


void generate_structure_name(char *project_path, Array *structures);
void generate_structure_methods(char *project_path, Array *structures);
void generate_includes(char *project_path, char *structures_path, Array *structures);


void generate_sources(char *project_path, char *structures_path) {
	char *path = string_copy(project_path);
	char *path_libraries = string_appends((char *[]){path, "/libraries", NULL});
	char *path_structures = string_appends((char *[]){path, "/", structures_path, NULL});

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
				Array_add(structures, array_Structure_arguments(Array_get(h_files, h_files_i), structure_source_code));
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
	
	generate_structure_name(project_path, structures);
	generate_structure_methods(project_path, structures);
	generate_includes(project_path, structures_path, structures);
	// TODO: 
	
	// char *structures_string = Array_to_string(structures);
	// puts(structures_string);
	
	{
		free(path);
		free(path_libraries);
		free(path_structures);
		
		Array_free(h_files);
		Array_free(structures);
		// free(structures_string);
	}
}

void generate_structure_name(char *project_path, Array *structures) {
	size_t structures_size = Array_size(structures);
	char *names, *names_strings;
	{
		size_t names_length, names_strings_length;
		FILE *names_stream = open_memstream(&names, &names_length), *names_strings_stream = open_memstream(&names_strings, &names_strings_length);
		for (int i=0; i<structures_size; i++) {
			char *structure_name = ((Structure *) Array_get(structures, i))->name;
			char *structure_name_upper = string_to_upper(structure_name);
			fprintf(names_stream, "%s%s", structure_name_upper, (i<structures_size-1)?",\n\t":"");
			fprintf(names_strings_stream, "\"%s\"%s", structure_name, (i<structures_size-1)?",\n\t":"");
			{
				structure_name = NULL;
				free(structure_name_upper);
			}
		}
		{
			fclose(names_stream);
			fclose(names_strings_stream);
		}
	}
	
	char *structure_name_h_path = string_appends((char *[]){project_path, "/structure/structure_name.h", NULL});
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
	
	char *structure_name_c_path = string_appends((char *[]){project_path, "/structure/structure_name.c", NULL});
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

void generate_structure_methods(char *project_path, Array *structures) {
	size_t structures_size = Array_size(structures);
	char *pass_methods, *to_string_methods, *json_encode_methods, *json_decode_methods;
	{
		size_t pass_methods_length, to_string_methods_length, json_encode_methods_length, json_decode_methods_length;
		FILE *pass_methods_stream = open_memstream(&pass_methods, &pass_methods_length), *to_string_methods_stream = open_memstream(&to_string_methods, &to_string_methods_length), *json_encode_methods_stream = open_memstream(&json_encode_methods, &json_encode_methods_length), *json_decode_methods_stream = open_memstream(&json_decode_methods, &json_decode_methods_length);
		for (int i=0; i<structures_size; i++) {
			char *structure_name = ((Structure *) Array_get(structures, i))->name;
			fprintf(pass_methods_stream, "%s_pass%s", structure_name, (i<structures_size-1)?",\n\t":"");
			fprintf(to_string_methods_stream, "%s_to_string%s", structure_name, (i<structures_size-1)?",\n\t":"");
			fprintf(json_encode_methods_stream, "%s_json_encode%s", structure_name, (i<structures_size-1)?",\n\t":"");
			fprintf(json_decode_methods_stream, "%s_json_decode%s", structure_name, (i<structures_size-1)?",\n\t":"");
		}
		{
			fclose(pass_methods_stream);
			fclose(to_string_methods_stream);
			fclose(json_encode_methods_stream);
			fclose(json_decode_methods_stream);
		}
	}
	
	char *structure_methods_c_path = string_appends((char *[]){project_path, "/structure/structure_methods.c", NULL});
	char *structure_methods_c_format = file_read(structure_methods_c_path);
	char *structure_methods_c_source_code;
	{
		size_t structure_methods_c_source_code_length;
		FILE *structure_methods_c_source_code_stream = open_memstream(&structure_methods_c_source_code, &structure_methods_c_source_code_length);
		fprintf(structure_methods_c_source_code_stream, structure_methods_c_format, pass_methods, to_string_methods, json_encode_methods, json_decode_methods);
		{
			fclose(structure_methods_c_source_code_stream);
		}
	}
	file_write(structure_methods_c_path, structure_methods_c_source_code);
	{
		free(pass_methods);
		free(to_string_methods);
		free(json_encode_methods);
		free(json_decode_methods);
		free(structure_methods_c_path);
		free(structure_methods_c_format);
		free(structure_methods_c_source_code);
	}
}

void generate_includes(char *project_path, char *structures_path, Array *structures) {
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
			char *structure_name_lower = string_to_lower(structure->name);
			fprintf(include_libraries_stream, "#include \"libraries/%s_library.h\"\n", structure_name_lower);
			{
				free(include_structure);
				free(structure_name_lower);
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

/*
void generate_structure_library_and_dependencies(char *project_path, char *structures_path, Structure *structure) {
	
	char *name_upper=NULL;
	char *path_structure_serialize_h=NULL;
	char *path_structure_serialize_c=NULL;
	char *PATH_ALL_INCLUDED_C=NULL;
	char *PATH_INCLUDES_H=NULL;
	// create *_library.h
	{
		char * (*methods[])(Structure *) = {
			generate_pass_method_declaration,
			generate_to_string_method_declaration,
			generate_json_encode_declaration,
			generate_json_decode_declaration,
			NULL
		};
		
		char *source_code;
		{
			size_t source_code_length;
			FILE *source_code_stream = open_memstream(&source_code, &source_code_length);
			fprintf(source_code_stream, "#ifndef %s_LIBRARY_H\n", name_upper);
			fprintf(source_code_stream, "#define %s_LIBRARY_H\n", name_upper);
			fprintf(source_code_stream, "\n");
			fprintf(source_code_stream, "#include \"includes.h\"\n");
			fprintf(source_code_stream, "\n");
			fprintf(source_code_stream, "\n");
			for (int i=0; methods[i] != NULL; i++) {
				char *method_code = methods[i](structure);
				fprintf(source_code_stream, "%s\n", method_code);
				fprintf(source_code_stream, "\n");
				free(method_code);
			}
			fprintf(source_code_stream, "#endif");
			fclose(source_code_stream);
		}
		file_write(path_structure_serialize_h, source_code);
		free(source_code);
	}
	
	// create *_library.c
	{
		char * (*methods[])(Structure *) = {
			generate_pass_method_definition,
			generate_to_string_method_definition,
			generate_json_encode_definition,
			generate_json_decode_definition,
			NULL
		};
		
		char *source_code;
		{
			size_t source_code_length;
			FILE *source_code_stream = open_memstream(&source_code, &source_code_length);
			fprintf(source_code_stream, "#include \"includes.h\"\n");
			fprintf(source_code_stream, "\n");
			fprintf(source_code_stream, "\n");
			for (int i=0; methods[i]!=NULL; i++) {
				char *method_code = methods[i](structure);
				fprintf(source_code_stream, "%s\n", method_code);
				fprintf(source_code_stream, "%s", (methods[i+1]!=NULL)?"\n":"");
				free(method_code);
			}
			fclose(source_code_stream);
		}
		file_write(path_structure_serialize_c, source_code);
		free(source_code);
	}
	
	// edit \'all_included.h\' file REMOVED
	// edit \'all_included.c\' file
	{		
		char *source_code = file_read(PATH_ALL_INCLUDED_C);
		
		char *code_to_string;
		{
			size_t code_to_string_length;
			FILE *code_to_string_stream = open_memstream(&code_to_string, &code_to_string_length);
			fprintf(code_to_string_stream, "%s\'s to string implementation\n", structure->name);
			fprintf(code_to_string_stream, "\t\tif (strcmp(\"%s\", curr->name)==0) {\n", structure->name);
			fprintf(code_to_string_stream, "\t\t\tstructure_string = %s_to_string(curr->pointer);\n", structure->name);
			fprintf(code_to_string_stream, "\t\t}\n");
			fprintf(code_to_string_stream, "\t\t// %%s");
			fclose(code_to_string_stream);
		}
		char *code_pass;
		{
			size_t code_pass_length;
			FILE *code_pass_stream = open_memstream(&code_pass, &code_pass_length);
			fprintf(code_pass_stream, "StructureUsageSet_pass_%s\' cast and call\n", structure->name);
			fprintf(code_pass_stream, "\tif (strcmp(\"%s\", structureUsage->name)==0) {\n", structure->name);
			fprintf(code_pass_stream, "\t\t%s_pass(structureUsageSet, (%s *) structureUsage->pointer);\n", structure->name, structure->name);
			fprintf(code_pass_stream, "\t}\n");
			fprintf(code_pass_stream, "\t// %%s");
			fclose(code_pass_stream);
		}
		char *code;
		{
			size_t code_length;
			FILE *code_stream = open_memstream(&code, &code_length);
			fprintf(
				code_stream,
				source_code,
				code_to_string, "%s", code_pass
			);
			fclose(code_stream);
		}
		file_write(PATH_ALL_INCLUDED_C, code);
		{
			free(source_code);
			free(code_to_string);
			free(code_pass);
			free(code);
		}
	}
	// edit \'includes.h\'
	{
		char *code;
		{
			size_t code_length;
			FILE *code_stream = open_memstream(&code, &code_length);
			fprintf(code_stream, "#ifndef INCLUDES_H\n");
			fprintf(code_stream, "#define INCLUDES_H\n");
			fprintf(code_stream, "\n");
			fprintf(code_stream, "#include <stdio.h>\n");
			fprintf(code_stream, "#include <stdlib.h>\n");
			fprintf(code_stream, "#include <string.h>\n");
			fprintf(code_stream, "\n");
			fprintf(code_stream, "#include \"utils/structure_usage.h\"\n");
			fprintf(code_stream, "#include \"utils/structure_usage_set.h\"\n");
			fprintf(code_stream, "\n");
			{
				DIR *d;
				struct dirent *dir;
				if ((d = opendir("src/structures")) != NULL) {
					while((dir = readdir(d)) != NULL) {
						if (
							!string_equals(dir->d_name, ".") &&
							!string_equals(dir->d_name, "..") &&
							dir->d_name[strlen(dir->d_name)-1]!='c'
						) {
							fprintf(code_stream, "#include \"structures/%s\"\n", dir->d_name);
						}
					}
					closedir(d);
				}
			}
			fprintf(code_stream, "\n");
			{
				DIR *d;
				struct dirent *dir;
				if ((d = opendir("src/libraries")) != NULL) {
					while((dir = readdir(d)) != NULL) {
						if (
							!string_equals(dir->d_name, ".") &&
							!string_equals(dir->d_name, "..") &&
							dir->d_name[strlen(dir->d_name)-1]!='c'
						) {
							fprintf(code_stream, "#include \"libraries/%s\"\n", dir->d_name);
						}
					}
					closedir(d);
				}
			}
			fprintf(code_stream, "\n");
			fprintf(code_stream, "#include \"utils/all_included.h\"\n");
			fprintf(code_stream, "\n");
			fprintf(code_stream, "#endif");
			fclose(code_stream);
		}
		file_write(PATH_INCLUDES_H, code);
		{
			free(code);
		}
	}
	
	{
		Structure_free(structure);
	}
}*/


char * generate_pass_method_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void %s_pass(StructureUsageSet *structureUsageSet, %s *%s);", structure->name, structure->name, structure->shortcut);
		fclose(code_stream);
	}
	return code;
}

char * generate_pass_method_definition(Structure *structure) {
	char *code;
	{
		Tabs *tabs = Tabs_create();
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "%svoid %s_pass(StructureUsageSet *structureUsageSet, %s *%s) {\n", Tabs_get(tabs), structure->name, structure->name, structure->shortcut); Tabs_increment(tabs);
		fprintf(code_stream, "%sStructureUsageSet_get(structureUsageSet, \"%s\", %s)->usage = 1;\n", Tabs_get(tabs), structure->name, structure->shortcut);
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			if (curr->type==STRUCTURE || curr->type==STRUCTURE_POINTER || curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY) {
				char *attribute_pointer = generate_attribute_pointer(structure, curr);
				
				fprintf(
					code_stream,
					"%sif (%s%s!=NULL) {\n",
					Tabs_get(tabs),
					(string_equals(structure->name, curr->data_type)) ? "structureUsageSet->stage!=0 && ": "",
					attribute_pointer
				); Tabs_increment(tabs);
				
				char *code_add_pointer;
				{
					size_t code_add_pointer_length;
					FILE *code_add_pointer_stream = open_memstream(&code_add_pointer, &code_add_pointer_length);
					fprintf(code_add_pointer_stream, "StructureUsageSet_add(structureUsageSet, \"%s\", %s", curr->data_type, attribute_pointer);
					fclose(code_add_pointer_stream);
					code_add_pointer_stream = open_memstream(&code_add_pointer, &code_add_pointer_length);
					if (curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY) {
						char *code_loop_format = generate_attribute_with_loop(tabs, structure, curr, false);
						char *code_loop;
						{
							size_t code_loop_length;
							FILE *code_loop_stream = open_memstream(&code_loop, &code_loop_length);
							fprintf(code_loop_stream, code_loop_format, "", code_add_pointer, ");");
							fclose(code_loop_stream);
						}
						fprintf(code_add_pointer_stream, "%s", code_loop);
						{
							free(code_loop_format);
							free(code_loop);
						}
					} else {
						fprintf(code_add_pointer_stream, "%s%s%s", Tabs_get(tabs), code_add_pointer, ");\n");
					}
					fclose(code_add_pointer_stream);
				}
				
				fprintf(code_stream, "%s", code_add_pointer); Tabs_decrement(tabs);
				fprintf(code_stream, "%s}\n", Tabs_get(tabs));
				{
					free(attribute_pointer);
					free(code_add_pointer);
				}
			}
		}
		Tabs_decrement(tabs);
		fprintf(code_stream, "%s}", Tabs_get(tabs));
		{
			Tabs_free(tabs);
			fclose(code_stream);
		}
	}
	return code;
}


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

char * generate_attribute_with_loop(Tabs *tabs, Structure *structure, Attribute *attribute, Boolean slash_n) {
	char *code_loop_start;
	{
		size_t code_loop_start_length;
		FILE *code_loop_start_stream = open_memstream(&code_loop_start, &code_loop_start_length);
		for (int i=0; i<attribute->dimension->size; i++, Tabs_increment(tabs)) {
			fprintf(
				code_loop_start_stream,
				"%sfor (int i_%d=0; i_%d<%s%s%s; i_%d++) {\n",
				Tabs_get(tabs),
				i,
				i,
				(i<attribute->dimension->static_size) ? "" : structure->shortcut, (i<attribute->dimension->static_size) ? "" : "->", attribute->dimension->dimensions[i],
				i
			);
		}
		fprintf(code_loop_start_stream, "%s", Tabs_get(tabs));
		fclose(code_loop_start_stream);
	}
	char *code_array_indexes;
	{
		size_t code_array_indexes_length;
		FILE *code_array_indexes_stream = open_memstream(&code_array_indexes, &code_array_indexes_length);
		for (int i=0; i<attribute->dimension->size; i++) {							
			fprintf(code_array_indexes_stream, "[i_%d]", i);
		}
		fclose(code_array_indexes_stream);
	}
	char *code_loop_end;
	{
		size_t code_loop_end_length;
		FILE *code_loop_end_stream = open_memstream(&code_loop_end, &code_loop_end_length);
		fprintf(code_loop_end_stream, "\n");
		for (int i=0; i<attribute->dimension->size; i++) {
			Tabs_decrement(tabs);
			fprintf(code_loop_end_stream, "%s}\n", Tabs_get(tabs));
			if (slash_n) {
				fprintf(code_loop_end_stream, "%sfprintf(string_stream, \"\\n\");\n", Tabs_get(tabs));
			}
		}
		fclose(code_loop_end_stream);
	}
	char *code_loop;
	{
		size_t code_loop_length;
		FILE *code_loop_stream = open_memstream(&code_loop, &code_loop_length);
		fprintf(
			code_loop_stream,
			"%%s"
			"%s"
			"%%s%s%%s"
			"%s",
			code_loop_start,
			code_array_indexes,
			code_loop_end
		);
		fclose(code_loop_stream);
	}
	{
		free(code_loop_start);
		free(code_array_indexes);
		free(code_loop_end);
	}
	return code_loop;
}

