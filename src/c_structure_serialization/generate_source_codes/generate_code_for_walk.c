#include <stdio.h>

#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_walk.h"


void generate_walk_declaration(FILE *h_stream, Tabs *tabs, Structure *structure){
	fprintf(
		h_stream,
		"%svoid %s_walk_process(PointerSet *pointerSet, Pointer *pointer);",
		Tabs_get(tabs), structure->name
	);
}

void generate_walk_definition(FILE *c_stream, Tabs *tabs, Structure *structure) {
}


void walk_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%s, %s));\n",
		Tabs_get(tabs), attribute->data_type_upper, attribute_pointer
	);
}

void walk_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sif (%4$s!=NULL) {\n"
		"%1$s%2$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%3$s, %4$s));\n"
		"%1$s},
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer
	);
}
