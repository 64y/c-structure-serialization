#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_library.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_to_string.h"


void generate_to_string_declaration(FILE *h_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		h_stream,
		"%1$schar * %2$s_to_string(void *structure);\n"
		"%1$svoid %2$s_to_string_process(FILE *structure_string_stream, PointerSet *pointerSet, Pointer *pointer);",
		Tabs_get(tabs), structure->name
	);
}

void generate_to_string_definition(FILE *c_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		c_stream,
		"%1$schar * %3$s_to_string(void *structure) {\n"
		"%1$s%2$sData *data = encode(TO_STRING, Pointer_create_by_name_pointer(%4$s, structure));\n"
		"%1$s%2$schar *structure_string = data->bytes;\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sdata->bytes_size = 0;\n"
		"%1$s%2$s%2$sfree(data);\n"
		"%1$s%2$s%2$sdata = NULL;\n"
		"%1$s%2$s}\n"
		"%1$s%2$sreturn structure_string;\n"
		"%1$s}\n"
		"%1$s\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper
	);
	
	void (*to_string_encode_methods[]) (FILE *, Tabs *, Attribute *, char *) = { NULL, 
		to_string_encode_primitive, to_string_encode_primitive, to_string_encode_structure, to_string_encode_structure,
		to_string_encode_primitive, to_string_encode_primitive, to_string_encode_structure, to_string_encode_structure
	};
	fprintf(
		c_stream,
		"%svoid %s_to_string_process(FILE *structure_string_stream, PointerSet *pointerSet, Pointer *pointer) {\n",
		Tabs_get(tabs), structure->name
	); Tabs_increment(tabs);
	fprintf(
		c_stream,
		"%1$s%2$s *%3$s = (%2$s *) pointer->pointer;\n",
		Tabs_get(tabs), structure->name, structure->shortcut
	);
	if (Structure_contains_array_attributes(structure)) {
		fprintf(
			c_stream,
			"%sbool is_last_element_in_array = false;\n",
			Tabs_get(tabs)
		);
	}
	for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
		fprintf(
			c_stream,
			"%1$s// %2$s->%3$s\n"
			"%1$sfprintf(structure_string_stream, \"\\n%%s: \", \"%3$s\");\n",
			Tabs_get(tabs), structure->shortcut, attribute->name
		);
		switch (attribute->type) {
			case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
				char *attribute_pointer = generate_attribute_pointer(structure, attribute, NULL);
				to_string_encode_methods[attribute->type](c_stream, tabs, attribute, attribute_pointer);
				{
					string_free(attribute_pointer);
				}
				break;
			}
			case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
				fprintf(
					c_stream,
					"%1$sfprintf(structure_string_stream, \"\\n\");\n"
					"%1$sis_last_element_in_array = false;\n",
					Tabs_get(tabs)
				);
				char *attribute_pointer, *code_indexes, *code_is_last;
				{
					size_t code_indexes_length, code_is_last_length;
					FILE *code_indexes_stream=open_memstream(&code_indexes, &code_indexes_length), *code_is_last_stream=open_memstream(&code_is_last, &code_is_last_length);
					for (int i=0; i<attribute->dimension->size; i++) {
						fprintf(c_stream, "%1$sfor (int i_%2$d=0; i_%2$d<%3$s; i_%2$d++) {\n", Tabs_get(tabs), i, attribute->dimension->dimensions[i]);
						fprintf(code_indexes_stream, "[i_%d]", i);
						fprintf(code_is_last_stream, "i_%d==%s-1%s", i, attribute->dimension->dimensions[i], (i<attribute->dimension->size-1)?" &&":"");
						Tabs_increment(tabs);
					}
					{
						fclose(code_indexes_stream);
						fclose(code_is_last_stream);
					}
				}
				attribute_pointer = generate_attribute_pointer(structure, attribute, code_indexes);
				to_string_encode_methods[attribute->type](c_stream, tabs, attribute, attribute_pointer);
				fprintf(
					c_stream,
					"%1$sfprintf(structure_string_stream, \"%%s\", (i_%3$ld<%4$s-1)?\", \":\"\");\n"
					"%1$sif (%5$s) {\n"
					"%1$s%2$sis_last_element_in_array = true;\n"
					"%1$s}\n",
					Tabs_get(tabs), Tabs_get_tab(tabs), attribute->dimension->size-1, attribute->dimension->dimensions[attribute->dimension->size-1], code_is_last
				);
				for (int i=attribute->dimension->size-1; i>=0; i--) {
					if (i<attribute->dimension->size-1) {
						fprintf(
							c_stream,
							"%sfprintf(structure_string_stream, \"%%s\", (is_last_element_in_array)?\"\":\"\\n\");\n",
							Tabs_get(tabs)
						);
					}
					Tabs_decrement(tabs);
					fprintf(c_stream, "%s}\n", Tabs_get(tabs));
				}
				{
					string_free(attribute_pointer);
					string_free(code_indexes);
					string_free(code_is_last);
				}
				break;
			}
			case NO_TYPE: {
				fprintf(stderr, "\'generate_to_string_method_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
				exit(1);
			}
		}
		fprintf(
			c_stream,
			"%sfprintf(structure_string_stream, \"%c\");\n",
			Tabs_get(tabs), (attribute->next!=NULL)?';':'.'
		);
	}	Tabs_decrement(tabs);
	fprintf(c_stream, "%s}", Tabs_get(tabs));
}


void to_string_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_string_stream, \"\\\'%s\\\'\", %s);\n",
		Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, attribute_pointer
	);
}

void to_string_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_string_stream, \"%%s@%%lX\", \"%s\", (long)(void *)%s);\n",
		Tabs_get(tabs), attribute->data_type, attribute_pointer
	);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%s, %s));\n", Tabs_get(tabs), attribute->data_type_upper, attribute_pointer);
	} else {
		fprintf(stream, "%1$sif (%4$s!=NULL) {\n%1$s%2$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%3$s, %4$s));\n%1$s}", Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer);
	}
}
