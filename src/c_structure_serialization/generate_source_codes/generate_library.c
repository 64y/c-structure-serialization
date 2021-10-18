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
#include "c_structure_serialization/generate_source_codes/generate_library.h"

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

void generate_library_source_code_for_structure(char *project_path, Structure *structure) {
	/*char *path_libraries = string_appends(project_path, "/libraries", NO_MORE_STRINGS);
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
	}*/
}


