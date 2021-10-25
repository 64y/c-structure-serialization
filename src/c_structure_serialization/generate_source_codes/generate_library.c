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
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"
#include "c_structure_serialization/generate_source_codes/generate_library.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_to_string.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_json_codec.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_byte_codec.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute, char *indexes) {
	char *pointer;
	{
		size_t pointer_length;
		FILE *pointer_stream = open_memstream(&pointer, &pointer_length);
		if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
			fprintf(pointer_stream, "&");
		}
		fprintf(pointer_stream, "%s->%s", structure->shortcut, attribute->name);
		if (indexes!=NULL) {
			fprintf(pointer_stream, "%s", indexes);
		}
		fclose(pointer_stream);
	}
	return pointer;
}


void generate_library_source_codes_for_structure(char *path_to_sources, Structure *structure) {
	char *path_to_libraries = string_appends(path_to_sources, "/libraries", NO_MORE_STRINGS);
	mkdir(path_to_libraries, 0777);
	char *library_h_file_name = string_appends(path_to_libraries, "/", structure->name_lower, "_library.h", NO_MORE_STRINGS);
	{
		size_t declaration_methods_size = 3;
		void (*declaration_methods[])(FILE *h_stream, Tabs *tabs, Structure *structure) = {
			generate_to_string_declaration,
			generate_json_codec_declaration,
			generate_byte_codec_declaration
		};
		Tabs *tabs = Tabs_create();
		FILE *h_stream = fopen(library_h_file_name, "w");
		fprintf(
			h_stream,
			"#ifndef %1$s_LIBRARY_H\n"
			"#define %1$s_LIBRARY_H\n"
			"\n"
			"#include \"includes.h\"\n"
			"\n",
			structure->name_upper
		);
		for (int i=0; i<declaration_methods_size; i++) {
			fprintf(h_stream, "\n");
			declaration_methods[i](h_stream, tabs, structure);
			fprintf(h_stream, "\n");
		}
		fprintf(
			h_stream,
			"\n"
			"#endif"
		);
		{
			Tabs_free(tabs);
			fclose(h_stream);
		}
	}
	char *library_c_file_name = string_appends(path_to_libraries, "/", structure->name_lower, "_library.c", NO_MORE_STRINGS);
	{
		size_t definition_methods_size = 3;
		void (*definition_methods[])(FILE *c_stream, Tabs *tabs, Structure *structure) = {
			generate_to_string_definition,
			generate_json_codec_definition,
			generate_byte_codec_definition
		};
		Tabs *tabs = Tabs_create();
		FILE *c_stream = fopen(library_c_file_name, "w");
		fprintf(
			c_stream,
			"#include \"includes.h\"\n"
			"\n"
		);
		for (int i=0; i<definition_methods_size; i++) {
			fprintf(c_stream, "\n");
			definition_methods[i](c_stream, tabs, structure);
			fprintf(c_stream, "\n");
		}
		{
			Tabs_free(tabs);
			fclose(c_stream);
		}
	}
	{
		string_free(path_to_libraries);
		string_free(library_h_file_name);
		string_free(library_c_file_name);
	}
}
