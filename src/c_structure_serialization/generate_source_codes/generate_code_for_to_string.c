#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_to_string.h"


void generate_to_string_declaration(FILE *h_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		h_stream,
		"%1$schar * %2$s_to_string(void *structure);\n"
		"%1$s\n"
		"%1$svoid %2$s_to_string_process(FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure);",
		Tabs_get(tabs), structure->name
	);
}

void generate_to_string_definition(FILE *c_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		c_stream,
		"%1$schar * %3$s_to_string(void *structure) {\n"
		"%1$s%2$sData *data = encode(TO_STRING, Pointer_create_by_name_pointer(%4$s, structure));\n"
		"%1$s%2$sdata->bytes_size = 0;\n"
		"%1$s%2$schar *structure_string = data->bytes;\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sfree(data);\n"
		"%1$s%2$s%2$sdata = NULL;\n"
		"%1$s%2$s}\n"
		"%1$s%2$sreturn structure_string;\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper
	);
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
