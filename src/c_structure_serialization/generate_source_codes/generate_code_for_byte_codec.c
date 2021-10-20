#include <stdio.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_sources.h"
#include "c_structure_serialization/generate_source_codes/generate_library.h"
#include "c_structure_serialization/generate_source_codes/generate_code_for_byte_codec.h"


void generate_byte_codec_declaration(FILE *h_stream, Structure *structure) {
	fprintf(
		h_stream,
		"%1$sData * %2$s_byte_encode(void *structure);\n"
		"%1$svoid * %2$s_byte_decode(Data *structure_data);\n"
		"%1$s\n"
		"%1$svoid %2$s_byte_encode_process(FILE *structure_byte_stream, PointerDictionary *pointerDictionary, void *structure);\n"
		"%1$svoid %2$s_byte_decode_process(FILE *structure_byte_stream, PointerDictionary *pointerDictionary, void *structure);",
		Tabs_get(tabs), structure->name
	);
}

void generate_byte_codec_definition(FILE *c_stream, Structure *structure) {
	fprintf(
		c_stream,
		"%1$sData * %3$s_byte_encode(void *structure) {\n"
		"%1$s%2$sData *data = encode(BYTE_ENCODE, Pointer_create_by_name_pointer(%4$s, structure));\n"
		"%1$s%2$sreturn data;\n"
		"%1$s}\n"
		"%1$s\n"
		"%1$svoid * %3$s_byte_decode(Data *structure_byte) {\n"
		"%1$s%2$s%3$s *%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$slong structure_address = 0;\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sFILE *structure_byte_stream = fmemopen(structure_byte->bytes, structure_byte->bytes_size, \"rb\");\n"
		"%1$s%2$s%2$sstructure_address = fread_uint32_value30bit_size2bit(structure_byte_stream);\n"
		"%1$s%2$s%2$s{\n"
		"%1$s%2$s%2$s%2$sfclose(structure_byte_stream);\n"
		"%1$s%2$s%2$s}\n"
		"%1$s%2$s}\n"
		"%1$s%2$svoid *structure = decode(\n"
		"%1$s%2$s%2$sBYTE_DECODE,\n"
		"%1$s%2$s%2$sPointer_create_by_name_pointer_address(%4$s, %5$s, structure_address),\n"
		"%1$s%2$s%2$sstructure_byte\n"
		"%1$s%2$s);\n"
		"%1$s%2$sreturn structure;\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper, structure->shortcut
	);
}


void byte_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfwrite(&%s, sizeof(%s), 1, structure_byte_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute->data_type
	);
}

void byte_encode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer){
	fprintf(
		stream,
		"%1$sif (%3$s==NULL) {\n"
		"%1$s%2$sstring_length = 0;\n"
		"%1$s%2$sfwrite(&string_length, sizeof(size_t), 1, structure_byte_stream);\n"
		"%1$s} else {\n"
		"%1$s%2$sstring_length = strlen(%3$s);\n"
		"%1$s%2$sfwrite(&string_length, sizeof(size_t), 1, structure_byte_stream);\n"
		"%1$s%2$sfwrite(%3$s, sizeof(char), strlen(%3$s), structure_byte_stream);\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute_pointer
	);
}

void byte_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$s{\n"
		"%1$s%2$sstructure_hashCode_stream = open_memstream(&structure_hashCode, &structure_hashCode_length);\n"
		"%1$s%2$sfprintf(structure_hashCode_stream, \"%%s@%%lX\", \"%3$s\", (long)(void *)%4$s);\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sfclose(structure_hashCode_stream);\n"
		"%1$s%2$s}\n"
		"%1$s}\n"
		"%1$sstructure_pointer = (PointerSet_contains_by_hashCode(pointerSet, structure_hashCode);\n"
		"%1$sfwrite_uint32_value30bit_size2bit(structure_byte_stream, structure_pointer->address_id);\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type, attribute_pointer
	);
}

void byte_decode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfread(&%s, sizeof(%s), 1, structure_byte_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute->data_type
	);
}

void byte_decode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfread(&string_length, sizeof(size_t), 1, structure_byte_stream);\n",
		Tabs_get(Tabs)
	);
	
	if (attribute->dimension==NULL || (attribute->dimension!=NULL && attribute->dimension->dynamic_size_source>0)) {
		fprintf(
			stream,
			"%1$sif (string_length!=0) {\n"
			"%1$s%2$sstring = (char *)calloc(string_length+1, sizeof(char));\n"
			"%1$s%2$sfread(string, sizeof(char), string_length, structure_byte_stream);\n"
			"%1$s%2$s%3$s = string;\n"
			"%1$s} else {\n"
			"%1$s%2$s%3$s = NULL;\n"
			"%1$s}\n",
			Tabs_get(tabs), Tabs_get_tab(tabs), attribute_pointer
		);
	} else {
		fprintf(
			stream,
			"%1$sif (string_length!=0) {\n"
			"%1$s%2$sstrcpy(, string);\n"
			"%1$s%2$s{\n"
			"%1$s%2$s%2$sfree(string);\n"
			"%1$s%2$s%2$sstring = NULL;\n"
			"%1$s%2$s}\n"
			"%1$s} else {\n"
			"%1$s%2$smemset(%3$s, 0x00, %4$s);\n"
			"%1$s}\n",
			Tabs_get(tabs), Tabs_get_tab(tabs), attribute_pointer, attribute->dimension->dimensions[attribute->dimension->size-1]
		);
	}

}

void byte_decode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sstructure_address = fread_uint32_value30bit_size2bit(structure_byte_stream);\n"
		"%1$sPointerSet_put(pointerSet, Pointer_create_by_name_pointer_address(%4$s, %5$s, structure_address));\n"
		"%1$s{\n"
		"%1$s%2$sstructure_address = 0;\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type, attribute->data_type_upper, attribute_pointer
	);
}

void byte_decode_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sstructure_address = fread_uint32_value30bit_size2bit(structure_byte_stream);\n"
		"%1$sif (structure_address!=0) {\n"
		"%1$s%2$sstructure_hashCode_stream = open_memstream(&structure_hashCode, &structure_hashCode_length);\n"
		"%1$s%2$sfprintf(structure_hashCode_stream, \"%%s@%%lX\", \"%3$s\", structure_address);\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sfclose(structure_hashCode_stream);\n"
		"%1$s%2$s}\n"
		"%1$s%2$sif (PointerSet_contains_by_hashCode(pointerSet, structure_hashCode)) {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *) PointerSet_get_by_hashCode(pointerSet, structure_hashCode);\n"
		"%1$s%2$s} else {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$s%2$sPointerSet_put(pointerSet, Pointer_create_by_name_pointer_hashCode(%4$s, %5$s, structure_hashCode));\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sstructure_address = 0;\n"
		"%1$s%2$s%2$sfree(structure_hashCode);\n"
		"%1$s%2$s%2$sstructure_hashCode = NULL;\n"
		"%1$s%2$s%2$sstructure_hashCode_length = 0;\n"
		"%1$s%2$s}\n"
		"%1$s} else {\n"
		"%1$s%2$s%5$s = NULL;\n"
		"%1$s}\n"
		"%1$s%2$s\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type, attribute->data_type_upper, attribute_pointer
	);
}
