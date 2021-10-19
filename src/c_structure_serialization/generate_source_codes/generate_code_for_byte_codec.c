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
		"%1$s%2$sreturn encode(BYTE_CODEC, Pointer_create_by_name_pointer(%4$s, structure));\n"
		"%1$s}"
		"%1$s\n"
		"%1$svoid * %3$s_byte_decode(Data *structure_data) {\n"
		"%1$s%2$s%3$s *%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$sreturn decode(BYTE_CODEC, Pointer_create_by_name_pointer(%4$s, %5$s), structure_data);\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->shortcut, structure->name_upper
	);
}


void byte_codec_out_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfwrite(&%s, sizeof(%s), 1, structure_byte_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute->data_type
	);
}

void byte_codec_out_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer){
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

void byte_codec_out_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sstructure_address = (long)(void *)%4$s;\n"
		"%1$sfwrite(&structure_address, sizeof(long), 1, structure_byte_stream);\n"
		"%1$sif (%4$s!=NULL) {\n"
		"%1$s%2$sPointerSet_put(pointerSet, Pointer_create_by_name_pointer(%3$s, %4$s));\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute_data_type_upper, attribute_pointer
	);
}

void byte_codec_in_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfread(&%s, sizeof(%s), 1, structure_byte_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute->data_type
	);
}

void byte_codec_in_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
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

void byte_codec_in_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	
}


void byte_codec_in_string(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%1$sfread(&string_length, sizeof(size_t), 1, structure_byte_stream);\n"
		"%1$sif (string_length!=0) {\n",
		Tabs_get(tabs)
	); Tabs_increment(tabs);
	fprintf(
		stream,
		"%1$sstring = (char *)calloc(string_length+1, sizeof(char));\n"
		"%1$sfread(string, sizeof(char), string_length, structure_byte_stream);\n",
		Tabs_get(tabs)
	);
	if (attribute->dimension==NULL || (attribute->dimension!=NULL && attribute->dimension->dynamic_size_source>0)) {
		fprintf(stream, "%s%s%s = string;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix); 
	} else {
		fprintf(stream, "%sstrcpy(%s%s, string);\n", Tabs_get(tabs), attribute_pointer, attribute_suffix);
		fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%sfree(string);\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
	} Tabs_decrement(tabs);
	fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	if (attribute->dimension==NULL || (attribute->dimension!=NULL && attribute->dimension->dynamic_size_source>0)) {
		fprintf(stream, "%s%s%s = NULL;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix); 
	} else {
		fprintf(stream, "%smemset(%s%s, 0x00, %s);\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->dimension->dimensions[attribute->dimension->size-1]);
	} Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		string_free(attribute_pointer);
	}
}

void byte_codec_in_structure(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {

	char *attribute_data_type_upper = string_to_upper(attribute->data_type);
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	
	fprintf(
		stream,
		"%1$sfread(&structure_address, sizeof(long), 1, structure_byte_stream);\n"
		"%1$sif (structure_address!=0) {\n",
		Tabs_get(tabs)
	); Tabs_increment(tabs);
	fprintf(
		stream,
		"%1$sFILE *hashCode_stream = open_memstream(&hashCode, &hashCode_length);\n"
		"%1$sfprintf(hashCode_stream, \"%%s@%%lX\", \"%2$s\", structure_address);\n",
		Tabs_get(tabs), attribute->data_type
	);
	fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%sfclose(hashCode_stream);\n", Tabs_get(tabs)); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%sPointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_data_type_upper, attribute_pointer, attribute_suffix);
	} else {
		fprintf(stream, "%sif (PointerDictionary_contains(pointerDictionary, hashCode)) {\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%s%s%s = (%s *) PointerDictionary_get(pointerDictionary, hashCode)->pointer;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type); Tabs_decrement(tabs);
		fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(
			stream,
			"%1$s%2$s%3$s = (%4$s *)malloc(sizeof(%4$s));\n"
			"%1$smemset(%2$s%3$s, 0x00, sizeof(%4$s));\n"
			"%1$sPointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, Pointer_create(%5$s, %2$s%3$s));\n",
			 Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type, attribute_data_type_upper
		); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
		
	}
	fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%sfree(hashCode);\n", Tabs_get(tabs));
	fprintf(stream, "%shashCode_length = 0;\n", Tabs_get(tabs)); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	Tabs_decrement(tabs);	
	fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%smemset(%s%s, 0x00, sizeof(%s));\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type);
	} else {
		fprintf(stream, "%s%s%s = NULL;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix);
	} Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		string_free(attribute_data_type_upper);
		string_free(attribute_pointer);
		attribute_suffix = NULL;
	}
}
