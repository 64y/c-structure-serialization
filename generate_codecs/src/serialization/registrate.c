#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils/basic_defines.h"
#include "utils/tabs.h"
#include "data_types/data_type.h"
#include "data_types/dimension.h"
#include "data_types/attribute.h"
#include "data_types/structure.h"
#include "data_types/structure_regular_expressions.h"

#include "serialization/structure_info.h"
#include "serialization/registrate.h"


char * serialize_attribute_with_loop(Tabs *tabs, Structure *structure, Attribute *attribute, Boolean slash_n);
char * serialize_attribute_pointer(Structure *structure, Attribute *attribute);


void Serialize_registrate_structure(char *structure_name, char *structure_file_name) {
	
	StructureInfo *structureInfo = StructureInfo_create(structure_name, structure_file_name);
	{
		if (
			access(structureInfo->path_structure_serialize_h, F_OK)==0 &&
			access(structureInfo->path_structure_serialize_c, F_OK)==0
		) {
			StructureInfo_free(structureInfo);
			return;
		}
	}
	Structure *structure = NULL;//RegularExpressions_parse_structure(structure_name, structureInfo->path_structure_h);
	// create *_library.h
	{
		char * (*methods[])(Structure *) = {
			serialize_method_pass_declaration,
			serialize_method_to_string_declaration,
			serialize_method_json_encode_declaration,
			serialize_method_json_decode_declaration,
			NULL
		};
		
		char *source_code;
		{
			size_t source_code_length;
			FILE *source_code_stream = open_memstream(&source_code, &source_code_length);
			fprintf(source_code_stream, "#ifndef %s_LIBRARY_H\n", structureInfo->name_upper);
			fprintf(source_code_stream, "#define %s_LIBRARY_H\n", structureInfo->name_upper);
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
		file_write(structureInfo->path_structure_serialize_h, source_code);
		free(source_code);
	}
	
	// create *_library.c
	{
		char * (*methods[])(Structure *) = {
			serialize_method_pass_definition,
			serialize_method_to_string_definition,
			serialize_method_json_encode_definition,
			serialize_method_json_decode_definition,
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
		file_write(structureInfo->path_structure_serialize_c, source_code);
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
		StructureInfo_free(structureInfo);
		Structure_free(structure);
	}
}

char * serialize_method_pass_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void %s_pass(StructureUsageSet *structureUsageSet, %s *%s);", structure->name, structure->name, structure->shortcut);
		fclose(code_stream);
	}
	return code;
}

char * serialize_method_pass_definition(Structure *structure) {
	char *code;
	{
		Tabs *tabs = Tabs_create();
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "%svoid %s_pass(StructureUsageSet *structureUsageSet, %s *%s) {\n", Tabs_get(tabs), structure->name, structure->name, structure->shortcut); Tabs_increment(tabs);
		fprintf(code_stream, "%sStructureUsageSet_get(structureUsageSet, \"%s\", %s)->usage = 1;\n", Tabs_get(tabs), structure->name, structure->shortcut);
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			if (curr->type==STRUCTURE || curr->type==STRUCTURE_POINTER || curr->type==STRUCTURE_ARRAY || curr->type==STRUCTURE_POINTER_ARRAY) {
				char *attribute_pointer = serialize_attribute_pointer(structure, curr);
				
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
						char *code_loop_format = serialize_attribute_with_loop(tabs, structure, curr, false);
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

char * serialize_method_to_string_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_to_string(void *pointer);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * serialize_method_to_string_definition(Structure *structure) {
	char *code;
	{
		Tabs *tabs = Tabs_create();
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		
		fprintf(code_stream, "%schar * %s_to_string(void *pointer) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(code_stream, "%s%s *%s = (%s *) pointer;\n", Tabs_get(tabs), structure->name, structure->shortcut, structure->name);
		fprintf(code_stream, "%ssize_t string_length;\n", Tabs_get(tabs));
		fprintf(code_stream, "%schar *string;\n", Tabs_get(tabs));
		fprintf(code_stream, "%sFILE *string_stream = open_memstream(&string, &string_length);\n", Tabs_get(tabs));
		fprintf(code_stream, "%sfprintf(string_stream, \"%s [@%%lx]:\\n\", (long)(void *)%s);\n", Tabs_get(tabs), structure->name, structure->shortcut);
		
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			char *attribute_name = string_copy(curr->name);
			char *attribute_pointer = serialize_attribute_pointer(structure, curr);
			char *attribute_format = NULL;
			char *attribute_delimeter = NULL;
			switch (curr->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					// attribute_format
					attribute_format = string_copy("%sfprintf(string_stream, \"%s%s%s\\n\",%s%s);\n");
					// attribute_delimeter
					attribute_delimeter = string_copy((curr->type==PRIMITIVE||curr->type==STRING)?": ":"->");
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					// attribute_format
					{
						char *attribute_array_format = serialize_attribute_with_loop(tabs, structure, curr, true);
						// free(attribute_format);
						size_t attribute_format_length;
						FILE *attribute_format_stream = open_memstream(&attribute_format, &attribute_format_length);
						fprintf(
							attribute_format_stream,
							attribute_array_format,
							"%sfprintf(string_stream, \"%s %s);\n",
							/* for {*/
							"fprintf(string_stream, \"%s \",%s%s", /*[...]*/ ");"
							/* } */
						);
						fclose(attribute_format_stream);
						free(attribute_array_format);
					}
					// attribute_delimeter
					{
						size_t attribute_delimeter_length;
						FILE *attribute_delimeter_stream = open_memstream(&attribute_delimeter, &attribute_delimeter_length);

						fprintf(attribute_delimeter_stream, "[");
						for (int i=0; i<curr->dimension->size; i++) {
							fprintf(attribute_delimeter_stream, "%%d%s", (i+1 < curr->dimension->size) ? " x " : "");
						}
						fprintf(attribute_delimeter_stream, "]");
						fprintf(attribute_delimeter_stream, "\\n\", ");

						for (int i=0; i<curr->dimension->size; i++) {
							fprintf(
								attribute_delimeter_stream,
								"%s%s%s%s",
								(i<curr->dimension->static_size) ? "" : structure->shortcut,
								(i<curr->dimension->static_size) ? "" : "->",
								curr->dimension->dimensions[i],
								(i+1<curr->dimension->size) ? ", ": ""
							);
						}
						fclose(attribute_delimeter_stream);
					}
					break;
				}
				case NO_TYPE:
					error("work with no typed attribute!");
			}
			char *attribute_format_specifier = NULL;
			char *attribute_cast = NULL;
			switch (curr->type) {
				case PRIMITIVE:	case STRING: case PRIMITIVE_ARRAY: case STRING_ARRAY: {
					// attribute_format_specifier
					{
						size_t attribute_format_specifier_length;
						FILE *attribute_format_specifier_stream = open_memstream(&attribute_format_specifier, &attribute_format_specifier_length);
						fprintf(attribute_format_specifier_stream, "\\\'%s\\\'", get_basic_type_by_name(curr->data_type)->format_specifier);
						fclose(attribute_format_specifier_stream);
					}
					// attribute_cast
					attribute_cast = string_copy(" ");
					break;
				}
				case STRUCTURE: case STRUCTURE_POINTER: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					// attribute_format_specifier
					attribute_format_specifier = string_copy("@%lx");
					// attribute_cast
					attribute_cast = string_copy(" (long)(void *)");
					break;
				}
				case NO_TYPE:
					error("work with no typed attribute!");
			}
			
			fprintf(
				code_stream,
				attribute_format,
				Tabs_get(tabs), attribute_name, attribute_delimeter, attribute_format_specifier, attribute_cast, attribute_pointer
			);
			
			{
				free(attribute_name);
				free(attribute_pointer);
				free(attribute_format);
				free(attribute_delimeter);
				free(attribute_format_specifier);
				free(attribute_cast);
			}
		}
		if (Structure_has_structure_attributes(structure)) {
			fprintf(code_stream, "%schar *pointers_string = pointers_to_string(\"%s\", %s);\n", Tabs_get(tabs), structure->name, structure->shortcut);
			fprintf(code_stream, "%sif (pointers_string != NULL) {\n", Tabs_get(tabs));	Tabs_increment(tabs);
			fprintf(code_stream, "%sfprintf(string_stream, \"%%s\", pointers_string);\n", Tabs_get(tabs));
			fprintf(code_stream, "%sfree(pointers_string);\n", Tabs_get(tabs));	Tabs_decrement(tabs);
			fprintf(code_stream, "%s}\n", Tabs_get(tabs));
		}
		fprintf(code_stream, "%sfclose(string_stream);\n", Tabs_get(tabs));
		fprintf(code_stream, "%sreturn string;\n", Tabs_get(tabs));	Tabs_decrement(tabs);
		fprintf(code_stream, "%s}", Tabs_get(tabs));
		{
			Tabs_free(tabs);
			fclose(code_stream);
		}
	}
	return code;
}

char * serialize_method_json_encode_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_json_encode(void *pointer);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * serialize_method_json_encode_definition(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_json_encode(void *pointer) {\n", structure->name);
		fprintf(code_stream, "\treturn NULL;\n");
		fprintf(code_stream, "}");
		fclose(code_stream);
	}
	return code;
}

char * serialize_method_json_decode_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void * %s_json_decode(char *json);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * serialize_method_json_decode_definition(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void * %s_json_decode(char *json) {\n", structure->name);
		fprintf(code_stream, "\treturn NULL;\n");
		fprintf(code_stream, "}");
		fclose(code_stream);
	}
	return code;
}


char * serialize_attribute_with_loop(Tabs *tabs, Structure *structure, Attribute *attribute, Boolean slash_n) {
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

char * serialize_attribute_pointer(Structure *structure, Attribute *attribute) {
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
