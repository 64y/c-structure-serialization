#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/tabs.h"
#include "c_structure_serialization/data_types/attribute_type.h"
#include "c_structure_serialization/data_types/basic_type.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/generate_source_codes/generate_bytes_codec.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"



char * generate_bytes_codec_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(
			code_stream,
			"void %1$s_bytes_encode_process(FILE *structure_bytes_stream, PointerDictionary *pointerDictionary, void *structure);\n"
			"void %1$s_bytes_decode_process(FILE *structure_bytes_stream, PointerDictionary *pointerDictionary, void *structure);\n"
			"\n"
			"Data * %1$s_bytes_encode(void *structure);\n"
			"void * %1$s_bytes_decode(Data *structure_bytes);",
			structure->name
		);
		fclose(code_stream);
	}
	return code;
}


void fwrite_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void fwrite_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void fwrite_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);

void fread_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void fread_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void fread_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);


char * generate_bytes_codec_definition(Structure *structure) {

	void (*array_of_printf_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		fwrite_primitive_value, fwrite_string_value, fwrite_structure_value, fwrite_structure_value,
		fwrite_primitive_value, fwrite_string_value, fwrite_structure_value, fwrite_structure_value
	};
	void (*array_of_scanf_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		fread_primitive_value, fread_string_value, fread_structure_value, fread_structure_value,
		fread_primitive_value, fread_string_value, fread_structure_value, fread_structure_value
	};
	char *code_bytes_encode_process, *code_bytes_decode_process;
	{
		size_t code_bytes_encode_process_length, code_bytes_decode_process_length;
		FILE *e = open_memstream(&code_bytes_encode_process, &code_bytes_decode_process_length), *d = open_memstream(&code_bytes_decode_process, &code_bytes_decode_process_length);
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		char *stream_name = string_copy("structure_bytes_stream");
		// encode
		fprintf(e, "%svoid %s_bytes_encode_process(FILE *structure_bytes_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increase(et);
		// decode
		fprintf(d, "%svoid %s_bytes_decode_process(FILE *structure_bytes_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increase(dt);
		
		// encode
		Tabs_decrease(et);
		fprintf(e, "%s}", Tabs_get(et));
		// decode
		Tabs_decrease(dt);
		fprintf(d, "%s}", Tabs_get(dt));
		{
			fclose(e);
			fclose(d);
			Tabs_free(et);
			Tabs_free(dt);
			free(stream_name);
		}
	}
	char *code_bytes_encode;
	{
		size_t code_bytes_encode_length;
		FILE *code_bytes_encode_stream = open_memstream(&code_bytes_encode, &code_bytes_encode_length);
		Tabs *tabs = Tabs_create();
		fprintf(code_bytes_encode_stream, "%sData * %s_bytes_encode(void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(code_bytes_encode_stream, "%sreturn bytes_encode(Pointer_create(%s, structure));\n", Tabs_get(tabs), structure->name_upper); Tabs_decrement(tabs);
		fprintf(code_bytes_encode_stream, "%s}", Tabs_get(tabs));
		{
			fclose(code_bytes_encode_stream);
			Tabs_free(tabs);
		}
	}
	char *code_bytes_decode;
	{
		size_t code_bytes_decode_length;
		FILE *code_bytes_decode_stream = open_memstream(&code_bytes_decode, &code_bytes_decode_length);
		Tabs *tabs = Tabs_create();
		fprintf(code_bytes_decode_stream, "%svoid * %s_bytes_decode(Data *structure_bytes) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(
			code_bytes_decode_stream,
			"%1$s%2$s *%3$s = (%2$s *)malloc(sizeof(%2$s));\n"
			"%1$smemset(%3$s, 0x00, sizeof(%3$s));\n"
			"%1$sreturn bytes_decode(structure_bytes, Pointer_create(%4$s, %3$s));\n",
			Tabs_get(tabs), structure->name, structure->shortcut, structure->name_upper
		); Tabs_decrement(tabs);
		fprintf(code_bytes_decode_stream, "%s}", Tabs_get(tabs));
		{
			fclose(code_bytes_decode_stream);
			Tabs_free(tabs);
		}
	}
	char *code = string_appends(
		(char *[]) {
			code_bytes_encode_process,
			"\n",
			code_bytes_decode_process,
			"\n",
			code_bytes_encode,
			"\n",
			code_bytes_decode,
			NULL
		}
	);
	{
		free(code_bytes_encode_process);
		free(code_bytes_decode_process);
		free(code_bytes_encode);
		free(code_bytes_decode);
	}
	return code;
}


void fwrite_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%sfwrite(%s->%s%s, sizeof(%s), 1, structure_bytes_stream);\n", Tabs_get(tabs), structure->name, attribute->name, attribute_suffix, attribute->data_type);
	{
		attribute_suffix = NULL;
	}
}

void fwrite_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%sif (%s%s==NULL) {\n", Tabs_get(tabs), attribute_pointer, attribute_suffix); Tabs_increment(tabs);
	fprintf(stream, "%sfwrite(0, sizeof(size_t), 1, structure_bytes_stream);\n", Tabs_get(tabs)); Tabs_decrement(tabs);
	fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%1$sfwrite(%2$s%3$s, sizeof(char), strlen(%2$s%3$s), structure_bytes_stream);\n", Tabs_get(tabs), attribute_pointer, attribute_suffix); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}

void fwrite_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_data_type_upper = string_to_upper(attribute->data_type);
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%1$sfwrite((long)(void *)%2$s%3$s, sizeof(long), 1, structure_bytes_stream);\n"
		"%1$sif (%2$s%3$s!=NULL) {\n",
		Tabs_get(tabs), attribute_pointer, attribute_suffix
	); Tabs_increment(tabs);
	fprintf(stream, "%sPointerDictionary_put_by_value(pointerDictionary, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_data_type_upper, attribute_pointer, attribute_suffix); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_data_type_upper);
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
	
}

void fread_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%sfread(%s->%s%s, sizeof(%s), 1, structure_bytes_stream);\n", Tabs_get(tabs), structure->name, attribute->name, attribute_suffix, attribute->data_type);
	{
		attribute_suffix = NULL;
	}
}

void fread_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%1$sfread(&string_length, sizeof(size_t), 1, structure_bytes_stream);\n"
		"%1$sif (string_length!=0) {\n",
		Tabs_get(tabs)
	); Tabs_increment(tabs);
	fprintf(
		stream,
		"%1$sstring = (char *)calloc(string_length+1, sizeof(char));\n"
		"%1$sfread(string, sizeof(char), string_length, structure_bytes_stream);\n",
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
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}

void fread_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {

	char *attribute_data_type_upper = string_to_upper(attribute->data_type);
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	
	fprintf(
		stream,
		"%1$sfread(&structure_address, sizeof(long), 1, structure_bytes_stream);\n"
		"%1$sif (structure_address!=0) {\n",
		Tabs_get(tabs)
	); Tabs_increment(tabs);
	fprintf(
		stream,
		"%1$sFILE *hashCode_stream = open_memstream(&hashCode, &hashCode_length);\n"
		"%1$sfprintf(hashCode_stream, \"%%s@%%lx\", \"%2$s\", structure_address);\n",
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
			"%1$sPointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, Pointer_create(%5$s, %2$s%3$s$s));\n",
			 Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type, attribute_data_type_upper
		); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
		
		fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%sfree(hashCode);\n", Tabs_get(tabs));
		fprintf(stream, "%shashCode_length = 0;\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
	} Tabs_decrement(tabs);	
	fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%smemset(%s%s, 0x00, sizeof(%s));\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type);
	} else {
		fprintf(stream, "%s%s%s = NULL;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix);
	} Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_data_type_upper);
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}

