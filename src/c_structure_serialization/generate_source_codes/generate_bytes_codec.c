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
#include "c_structure_serialization/generate_source_codes/generate_bytes_codec.h"


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

	void (*array_of_fwrite_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		fwrite_primitive_value, fwrite_string_value, fwrite_structure_value, fwrite_structure_value,
		fwrite_primitive_value, fwrite_string_value, fwrite_structure_value, fwrite_structure_value
	};
	void (*array_of_fread_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		fread_primitive_value, fread_string_value, fread_structure_value, fread_structure_value,
		fread_primitive_value, fread_string_value, fread_structure_value, fread_structure_value
	};
	char *code_bytes_encode_process, *code_bytes_decode_process;
	{
		size_t code_bytes_encode_process_length, code_bytes_decode_process_length;
		FILE *e = open_memstream(&code_bytes_encode_process, &code_bytes_encode_process_length), *d = open_memstream(&code_bytes_decode_process, &code_bytes_decode_process_length);
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		char *stream_name = string_copy("structure_bytes_stream");
		// encode
		fprintf(e, "%svoid %s_bytes_encode_process(FILE *structure_bytes_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(et), structure->name); Tabs_increment(et);
		// decode
		fprintf(d, "%svoid %s_bytes_decode_process(FILE *structure_bytes_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(dt), structure->name); Tabs_increment(dt);
		if (Structure_contains_string_attributes(structure)) {
			//encode
			fprintf(e, "%ssize_t string_length;\n", Tabs_get(dt)
			);
			//decode
			fprintf(
				d,
				"%1$schar *string;\n"
				"%1$ssize_t string_length;\n",
				Tabs_get(dt)
			);
		}
		if (Structure_contains_structure_attributes(structure)) {
			//encode
			//decode
			fprintf(
				d,
				"%1$schar *hashCode;\n"
				"%1$ssize_t hashCode_length;\n"
				"%1$slong structure_address;\n",
				Tabs_get(dt)
			);
		}
		// encode
		fprintf(e, "%s%s *%s = (%s *) structure;\n", Tabs_get(et), structure->name, structure->shortcut, structure->name);
		// decode
		fprintf(d, "%s%s *%s = (%s *) structure;\n", Tabs_get(dt), structure->name, structure->shortcut, structure->name);
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			void (*fwrite_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_fwrite_value[attribute->type];
			void (*fread_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_fread_value[attribute->type];
			switch (attribute->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					// encode
					fwrite_value(e, et, structure, attribute, NULL);
					// decode
					fread_value(d, dt, structure, attribute, NULL);
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					int number_of_stars = attribute->dimension->dynamic_size_source + (attribute->type==STRUCTURE_POINTER_ARRAY);
					char *code_indexes;
					{
						size_t code_indexes_length;
						FILE *code_indexes_stream=open_memstream(&code_indexes, &code_indexes_length);
						fprintf(code_indexes_stream, "%s", "");
						fflush(code_indexes_stream);
						for (int i=0; i<attribute->dimension->size; i++, Tabs_increment(et), Tabs_increment(dt)) {
							// encode
							fprintf(e, "%1$sfor (int i_%2$d=0; i_%2$d<%3$s; i_%2$d++) {\n", Tabs_get(et), i, attribute->dimension->dimensions[i]);
							// decode
							if (i>=attribute->dimension->static_size_source) {
								char *stars_first = string_repeat_star(number_of_stars);
								char *stars_second = string_repeat_star(number_of_stars-1);
								fprintf(d, "%1$s%2$s->%3$s%4$s = (%5$s%6$s)calloc(%7$s, sizeof(%5$s%8$s));\n", Tabs_get(dt), structure->shortcut, attribute->name, code_indexes, attribute->data_type, stars_first, attribute->dimension->dimensions[i], stars_second);
								number_of_stars = number_of_stars - 1;
								{
									free(stars_first);
									free(stars_second);
								}
							}
							fprintf(d, "%1$sfor (int i_%2$d=0; i_%2$d<%3$s; i_%2$d++) {\n", Tabs_get(dt), i, attribute->dimension->dimensions[i]);
							fprintf(code_indexes_stream, "[i_%d]", i);
							fflush(code_indexes_stream);
						}
						{
							fclose(code_indexes_stream);
						}
					}
					// encode
					fwrite_value(e, et, structure, attribute, code_indexes);
					// decode
					fread_value(d, dt, structure, attribute, code_indexes);
					
					for (int i=0; i<attribute->dimension->size; i++) {
						// encode
						Tabs_decrement(et);
						fprintf(e, "%s}\n", Tabs_get(et));
						// decode
						Tabs_decrement(dt);
						fprintf(d, "%s}\n", Tabs_get(dt));
					}
					{
						free(code_indexes);
					}
					break;
				}
				case NO_TYPE: {
					fprintf(stderr, "\'generate_bytes_codec_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
					exit(1);
				}
			}
			{
				fwrite_value = NULL;
				fread_value = NULL;
			}
		}
		// encode
		Tabs_decrement(et);
		fprintf(e, "%s}", Tabs_get(et));
		// decode
		Tabs_decrement(dt);
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
	fprintf(stream, "%sfwrite(&%s->%s%s, sizeof(%s), 1, structure_bytes_stream);\n", Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix, attribute->data_type);
	{
		attribute_suffix = NULL;
	}
}

void fwrite_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%sif (%s%s==NULL) {\n", Tabs_get(tabs), attribute_pointer, attribute_suffix); Tabs_increment(tabs);
	fprintf(
		stream,
		"%1$sstring_length = 0;\n"
		"%1$sfwrite(&string_length, sizeof(size_t), 1, structure_bytes_stream);\n",
		Tabs_get(tabs)
	); Tabs_decrement(tabs);
	fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(
		stream,
		"%1$sstring_length = strlen(%2$s%3$s);\n"
		"%1$sfwrite(&string_length, sizeof(size_t), 1, structure_bytes_stream);\n"
		"%1$sfwrite(%2$s%3$s, sizeof(char), strlen(%2$s%3$s), structure_bytes_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute_suffix);
	Tabs_decrement(tabs);
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
		"%1$sfwrite((long *)(void **)&%2$s->%3$s%5$s, sizeof(long), 1, structure_bytes_stream);\n"
		"%1$sif (%4$s%5$s!=NULL) {\n",
		Tabs_get(tabs), structure->shortcut, attribute->name, attribute_pointer, attribute_suffix
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
	fprintf(stream, "%sfread(&%s->%s%s, sizeof(%s), 1, structure_bytes_stream);\n", Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix, attribute->data_type);
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
