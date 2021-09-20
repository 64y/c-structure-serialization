


#include "utils/basic_defines.h"
#include "utils/tabs.h"
#include "serialization/generate_sources.h"
#include "serialization/generate_to_string_method.h"


char * generate_to_string_method_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_to_string(void *pointer);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * generate_to_string_method_definition(Structure *structure) {
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
			char *attribute_pointer = generate_attribute_pointer(structure, curr);
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
						char *attribute_array_format = generate_attribute_with_loop(tabs, structure, curr, true);
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
