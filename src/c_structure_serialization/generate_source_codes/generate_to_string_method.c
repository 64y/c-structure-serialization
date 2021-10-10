#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"
#include "c_structure_serialization/generate_source_codes/generate_to_string_method.h"


char * generate_to_string_method_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(
			code_stream,
			"void %1$s_to_string_process(FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure);\n"
			"\n"
			"char * %1$s_to_string(void *structure);",
			structure->name
		);
		fclose(code_stream);
	}
	return code;
}


void printf_primitive(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void printf_structure(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);

char * generate_to_string_method_definition(Structure *structure) {
	void (*printf_methods[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL, 
		printf_primitive, printf_primitive, printf_structure, printf_structure,
		printf_primitive, printf_primitive, printf_structure, printf_structure
	};
	char *code_structure_to_string_process;
	{
		size_t code_structure_to_string_process_length;
		FILE *s = open_memstream(&code_structure_to_string_process, &code_structure_to_string_process_length);
		
		Tabs *tabs = Tabs_create();
		
		char *stream_name = string_copy("structure_string_stream");
		fprintf(s, "%svoid %s_to_string_process(FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(s, "%s%s *%s = (%s *) structure;\n", Tabs_get(tabs), structure->name, structure->shortcut, structure->name);
		//
		if (Structure_contains_array_attributes(structure)) {
			fprintf(s, "%sBoolean is_last_element_in_array = false;\n", Tabs_get(tabs));
		}
		fprintf(s, "%sfprintf(%s, \"%%s@%%lX\", \"%s\", (long)(void *) %s);\n", Tabs_get(tabs), stream_name, structure->name, structure->shortcut);
		fprintf(s, "%sif (%s != NULL) {\n", Tabs_get(tabs), structure->shortcut); Tabs_increment(tabs);
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			fprintf(s, "%s// %s->%s\n", Tabs_get(tabs), structure->shortcut, attribute->name);
			fprintf(s, "%sfprintf(%s, \"\\n%%s: \", \"%s\");\n", Tabs_get(tabs), stream_name, attribute->name);
			switch (attribute->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					printf_methods[attribute->type](s, tabs, structure, attribute, "");
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					fprintf(s, "%sfprintf(%s, \"\\n\");\n", Tabs_get(tabs), stream_name);
					fprintf(s, "%sis_last_element_in_array = false;\n", Tabs_get(tabs));
					char *code_loop, *code_indexes, *code_is_last;
					{
						size_t code_loop_length, code_indexes_length, code_is_last_length;
						FILE *code_loop_stream=open_memstream(&code_loop, &code_loop_length), *code_indexes_stream=open_memstream(&code_indexes, &code_indexes_length), *code_is_last_stream=open_memstream(&code_is_last, &code_is_last_length);
						for (int i=0; i<attribute->dimension->size; i++) {
							fprintf(code_loop_stream, "%sfor (int i_%d=0; i_%d<%s; i_%d++) {\n", Tabs_get(tabs), i, i, attribute->dimension->dimensions[i], i);
							fprintf(code_indexes_stream, "[i_%d]", i);
							fprintf(code_is_last_stream, "i_%d==%s-1%s", i, attribute->dimension->dimensions[i], (i<attribute->dimension->size-1)?" &&":"");
							Tabs_increment(tabs);
						}
						{
							fclose(code_loop_stream);
							fclose(code_indexes_stream);
							fclose(code_is_last_stream);
						}
					}
					fprintf(s, "%s", code_loop);
					printf_methods[attribute->type](s, tabs, structure, attribute, code_indexes);
					fprintf(s, "%sfprintf(%s, \"%%s\", (i_%ld<%s-1)?\", \":\"\");\n", Tabs_get(tabs), stream_name, attribute->dimension->size-1, attribute->dimension->dimensions[attribute->dimension->size-1]);
					fprintf(s, "%sif (%s) {\n", Tabs_get(tabs), code_is_last); Tabs_increment(tabs);
					fprintf(s, "%sis_last_element_in_array = true;\n", Tabs_get(tabs)); Tabs_decrement(tabs);
					fprintf(s, "%s}\n", Tabs_get(tabs));
					for (int i=attribute->dimension->size-1; i>=0; i--) {
						if (i<attribute->dimension->size-1) {
							fprintf(s, "%sfprintf(%s, \"%%s\", (is_last_element_in_array)?\"\":\"\\n\");\n", Tabs_get(tabs), stream_name);
						}
						Tabs_decrement(tabs);
						fprintf(s, "%s}\n", Tabs_get(tabs));
					}
					{
						free(code_loop);
						free(code_indexes);
						free(code_is_last);
					}
					// fprintf(s, "%s\n", Tabs_get(tabs));
					break;
				}
				case NO_TYPE: {
					fprintf(stderr, "\'generate_to_string_method_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
					exit(1);
				}
			}
			fprintf(s, "%sfprintf(%s, \"%c\");\n", Tabs_get(tabs), stream_name, (attribute->next!=NULL)?';':'.');
		}
		//
		Tabs_decrement(tabs);
		fprintf(s, "%s}\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(s, "%s}", Tabs_get(tabs));
		
		{
			fclose(s);
			Tabs_free(tabs);
			free(stream_name);
		}
	}
	char *code_structure_to_string;
	{
		size_t code_structure_to_string_length;
		FILE *s = open_memstream(&code_structure_to_string, &code_structure_to_string_length);
		
		Tabs *tabs = Tabs_create();
		
		fprintf(s, "%schar * %s_to_string(void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(s, "%sreturn to_string(Pointer_create(%s, structure));\n", Tabs_get(tabs), structure->name_upper); Tabs_decrement(tabs);
		fprintf(s, "%s}", Tabs_get(tabs));
		{
			fclose(s);
			Tabs_free(tabs);
		}
	}
	char * code = string_appends((char *[]) {code_structure_to_string_process, "\n", code_structure_to_string, NULL});
	{
		free(code_structure_to_string_process);
		free(code_structure_to_string);
	}
	return code;
}


void printf_primitive(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	fprintf(
		stream,
		"%sfprintf(structure_string_stream, \"\\\'%s\\\'\", %s->%s%s);\n",
		Tabs_get(tabs),
		BasicType_get_by_name(attribute->data_type)->format_specifier,
		structure->shortcut, attribute->name, indexes
	);
}

void printf_structure(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_name_upper = string_to_upper(attribute->data_type);
	fprintf(stream, "%sfprintf(structure_string_stream, \"%%s@%%lX\", \"%s\", (long)(void *) %s%s);\n", Tabs_get(tabs), attribute->data_type, attribute_pointer, indexes);
	fprintf(stream, "%sif (%s%s%s!=NULL) {\n", Tabs_get(tabs), (string_equals(structure->name, attribute->data_type))?"pointerDictionary->stage!=0 && ":"", attribute_pointer, indexes); Tabs_increment(tabs);
	fprintf(stream, "%sPointerDictionary_put_by_value(pointerDictionary, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_name_upper, attribute_pointer, indexes);
	Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_pointer);
		free(attribute_name_upper);
	}
}
