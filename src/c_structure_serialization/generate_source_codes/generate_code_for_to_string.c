#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_to_string.h"


void generate_to_string_declarations(FILE *h_stream, Tabs *tabs, Structure *structure) {
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
		"%1$s%2$sreturn to_string(Pointer_create(%4$s, structure));\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper
	);
}


void to_string_out_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_string_stream, \"\\\'%s\\\'\", %s);\n",
		Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, attribute_pointer
	);
}

void to_string_out_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_string_stream, \"%%s@%%lX\", \"%s\", (long)(void *)%s);\n",
		Tabs_get(tabs), attribute->data_type, attribute_pointer
	);
}
