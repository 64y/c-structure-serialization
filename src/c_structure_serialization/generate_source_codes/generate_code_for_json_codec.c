#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_sources.h"
#include "c_structure_serialization/generate_source_codes/generate_library.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_json_codec.h"


void generate_json_codec_declaration(FILE *h_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		h_stream,
		"%1$schar * %2$s_json_encode(void *structure);\n"
		"%1$svoid * %2$s_json_decode(char *structure_json);\n"
		"%1$s\n"
		"%1$svoid %2$s_json_encode_process(FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure);\n"
		"%1$svoid %2$s_json_decode_process(FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure);",
		Tabs_get(tabs), structure->name
	);
}

void generate_json_codec_definition(FILE *c_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		c_stream,
		"%1$schar * %3$s_json_encode(void *structure) {\n"
		"%1$s%2$sreturn json_encode(Pointer_create(%4$s, structure));\n"
		"%1$s}\n"
		"%1$s\n"
		"%1$svoid * %3$s_json_decode(char *structure_json) {\n"
		"%1$s%2$s%3$s *%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$sreturn json_decode(structure_json, Pointer_create(%4$s, %5$s));\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper, structure->shortcut
	);
}

void json_codec_out_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_json_stream, \"%s\", %s);\n",
		Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, attribute_pointer
	);
}

void json_codec_out_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sstring_base64 = (%3$s!=NULL) ? base64_encode_string(%3$s) : base64_encode(&((Data) {3, (byte *) \"\\0\\0\\0\"})) ;\n"
		"%1$sfprintf(structure_json_stream, \"\\\"%%s\\\"\", string_base64);\n"
		"%1$s{\n"
		"%1$s%2$sfree(string_base64);\n"
		"%1$s%2$sstring_base64 = NULL;\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute_pointer
	);
}

void json_codec_out_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_json_stream, \"%%s@%%lX\", \"%s\", (long)(void *)%s);\n",
		Tabs_get(tabs), attribute->data_type, attribute_pointer
	);
}

void json_codec_in_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfscanf(structure_json_stream, \"%s, \", &%s);\n",
		Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, attribute_pointer
	);
}

void json_codec_in_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sfscanf(structure_json_stream, \"\\\"\");\n"
		"%1$sfscanf(structure_json_stream, \"%%*[+/0-9=A-Za-z]%%ln\", &string_base64_length);\n"
		"%1$sfseek(structure_json_stream, -string_base64_length, SEEK_CUR);\n"
		"%1$sstring_base64 = (char *)calloc(string_base64_length+1, sizeof(char));\n"
		"%1$sfscanf(structure_json_stream, \"%%[+/0-9=A-Za-z]\", string_base64);\n"
		"%1$sfscanf(structure_json_stream, \"\\\", \");\n"
		"%1$sstring = base64_decode_string(string_base64);\n",
		Tabs_get(tabs)
	);
	
	if (attribute->dimension==NULL || (attribute->dimension!=NULL && attribute->dimension->dynamic_size_source>0)) {
		fprintf(
			stream,
			"%1$sif (strcmp(\"AAAA\", string_base64)==0) {\n"
			"%1$s%2$s%3$s = NULL;\n"
			"%1$s%2$s{\n"
			"%1$s%2$s%2$sfree(string);\n"
			"%1$s%2$s%2$sstring = NULL;\n"
			"%1$s%2$s}\n"
			"%1$s} else {\n"
			"%1$s%2$s%3$s = string;\n"
			"%1$s}\n"
			"%1$s{\n"
			"%1$s%2$sfree(string_base64);\n"
			"%1$s%2$sstring_base64 = NULL;\n"
			"%1$s%2$sstring_base64_length = 0;\n"
			"%1$s}\n",
			Tabs_get(tabs), Tabs_get_tab(tabs), attribute_pointer
		);
	} else {
		fprintf(
			stream,
			"%1$sstrcpy(%3$s, string);\n"
			"%1$s{\n"
			"%1$s%2$sfree(string);\n"
			"%1$s%2$sstring = NULL;\n"
			"%1$s%2$sfree(string_base64);\n"
			"%1$s%2$sstring_base64 = NULL;\n"
			"%1$s%2$sstring_base64_length = 0;\n"
			"%1$s}\n",
			Tabs_get(tabs), Tabs_get_tab(tabs), attribute_pointer
		);
	}
}

void json_codec_in_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sfscanf(structure_json_stream, \"%%*[0-9@A-Z_a-z]%%ln\", &structure_hashCode_length);\n"
		"%1$sfseek(structure_json_stream, -structure_hashCode_length, SEEK_CUR);\n"
		"%1$sstructure_hashCode = (char *)calloc(structure_hashCode_length+1, sizeof(char));\n"
		"%1$sfscanf(structure_json_stream, \"%%[0-9@A-Z_a-z], \", sstructure_hashCode);\n"
		"%1$ssscanf(hashCode, \"%%*[^@]@%%lX\", &structure_address);\n"
		"%1$sPointerSet_put(pointerSet, Pointer_create_by_name_pointer_hashCode(%3$s, %4$s, structure_hashCode));\n"
		"%1$s{\n"
		"%1$s%2$sfree(structure_hashCode);\n"
		"%1$s%2$sstructure_hashCode = NULL;\n"
		"%1$s%2$sstructure_hashCode_length = 0;\n"
		"%1$s%2$sstructure_address = 0;\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer
	);
}

void json_codec_in_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sfscanf(structure_json_stream, \"%%*[0-9@A-Z_a-z]%%ln\", &structure_hashCode_length);\n"
		"%1$sfseek(structure_json_stream, -structure_hashCode_length, SEEK_CUR);\n"
		"%1$sstructure_hashCode = (char *)calloc(structure_hashCode_length+1, sizeof(char));\n"
		"%1$sfscanf(structure_json_stream, \"%%[0-9@A-Z_a-z], \", structure_hashCode);\n"
		"%1$ssscanf(hashCode, \"%%*[^@]@%%lX\", &structure_address);\n"
		"%1$sif(structure_address==0) {\n"
		"%1$s%2$s%5$s = NULL;\n"
		"%1$s} else {\n"
		"%1$s%2$sif (PointerSet_contains_by_hashCode(pointerSet, hashCode)) {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *) PointerSet_get_by_hashCode(pointerSet, hashCode);\n"
		"%1$s%2$s} else {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$s%2$sPointerSet_put(Pointer_create_by_name_pointer_hashCode(%4$s, %5$s, structure_hashCode));\n"
		"%1$s%2$s}\n"
		"%1$s}\n"
		"%1$s{\n"
		"%1$s%2$sfree(structure_hashCode);\n"
		"%1$s%2$sstructure_hashCode = NULL;\n"
		"%1$s%2$sstructure_hashCode_length = 0;\n"
		"%1$s%2$sstructure_address = 0;\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type, attribute->data_type_upper, attribute_pointer
	);
}
