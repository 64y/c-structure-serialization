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


char * generate_json_codec_declaration(Structure *structure) {
	char *code = string_create_by_format(
		"void %1$s_json_encode_process(FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure);\n"
		"void %1$s_json_decode_process(FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure);\n"
		"\n"
		"char * %1$s_json_encode(void *structure);\n"
		"void * %1$s_json_decode(char *structure_json);",
		structure->name
	);
	return code;
}


void printf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void printf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void printf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);

char * generate_json_codec_definition(Structure *structure) {
	void (*array_of_printf_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		printf_primitive_value, printf_string_value, printf_structure_value, printf_structure_value,
		printf_primitive_value, printf_string_value, printf_structure_value, printf_structure_value
	};
	void (*array_of_scanf_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		scanf_primitive_value, scanf_string_value, scanf_structure_value, scanf_structure_value,
		scanf_primitive_value, scanf_string_value, scanf_structure_value, scanf_structure_value
	};
	char *code_json_encode_process, *code_json_decode_process;
	{
		size_t code_json_encode_process_length, code_json_decode_process_length;
		FILE *e = open_memstream(&code_json_encode_process, &code_json_encode_process_length), *d = open_memstream(&code_json_decode_process, &code_json_decode_process_length);
		
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		// start
		char *stream_name = string_create("structure_json_stream");

		//       encode
		fprintf(e, "%svoid %s_json_encode_process(FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(et), structure->name); Tabs_increment(et);
		fprintf(e, "%sif (structure==NULL) return;\n", Tabs_get(et));
		//       decode
		fprintf(d, "%svoid %s_json_decode_process(FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(dt), structure->name); Tabs_increment(dt);
		fprintf(d, "%sif (structure==NULL) return;\n", Tabs_get(et));
		//
		if (Structure_contains_string_attributes(structure)) {
			// encode
			fprintf(e, "%schar *string_base64;\n", Tabs_get(et));
			// decode
			fprintf(
				d,
				"%1$schar *string, *string_base64;\n"
				"%1$ssize_t string_base64_length;\n",
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
		//
		//       encode
		fprintf(
			e,
			"%1$s%2$s *%3$s = (%4$s *) structure;\n"
			"%1$sfprintf(%5$s, \"{\");\n",
			Tabs_get(et), structure->name, structure->shortcut, structure->name, stream_name
		);
		//       decode
		fprintf(
			d,
			"%1$s%2$s *%3$s = (%4$s *) structure;\n"
			"%1$sfscanf(%5$s, \"{\");\n",
			Tabs_get(dt), structure->name, structure->shortcut, structure->name, stream_name
		);
		// structure
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			char *attribute_pointer = generate_attribute_pointer(structure, attribute);
			void (*attribute_printf_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_printf_value[attribute->type];
			void (*attribute_scanf_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_scanf_value[attribute->type];
			// encode
			fprintf(
				e,
				"%1$s// attribute \\\'%2$s\\\'\n"
				"%1$sfprintf(%3$s, \"\\n\\t\\\"%2$s\\\": \");\n",
				Tabs_get(et), attribute->name, stream_name
			);
			// decode
			fprintf(
				d,
				"%1$s// attribute \\\'%2$s\\\'s\n"
				"%1$sfscanf(%3$s, \"\\n\\t\\\"%2$s\\\": \");\n",
				Tabs_get(dt), attribute->name, stream_name
			);
			//
			switch (attribute->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					attribute_printf_value(e, et, structure, attribute, NULL);
					attribute_scanf_value(d, dt, structure, attribute, NULL);
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					char *code_for, *indexes;
					FILE *indexes_stream;
					{
						size_t indexes_length;
						indexes_stream = open_memstream(&indexes, &indexes_length);
						fprintf(indexes_stream, "%s", "");
						fflush(indexes_stream);
					}
					
					int number_of_stars = attribute->dimension->dynamic_size_source + (attribute->type==STRUCTURE_POINTER_ARRAY);
					for (int i=0; i<attribute->dimension->size; i++) {
						// decode
						if (i>=attribute->dimension->static_size_source) {
							char *stars_first = string_repeat_star(number_of_stars);
							char *stars_second = string_repeat_star(number_of_stars-1);
							fprintf(
								d,
								"%s%s%s = (%s%s)calloc(%s, sizeof(%s%s));\n",
								Tabs_get(dt),
								attribute_pointer, indexes,
								attribute->data_type, stars_first,
								attribute->dimension->dimensions[i],
								attribute->data_type, stars_second
							);
							{
								free(stars_first);
								free(stars_second);
							}
							number_of_stars = number_of_stars - 1;
						}
						//
						{	// creating for here
							size_t code_for_length;
							FILE *code_for_stream = open_memstream(&code_for, &code_for_length);
							fprintf(code_for_stream, "for (int i_%1$d=0; i_%1$d<%2$s; i_%1$d++) {", i, attribute->dimension->dimensions[i]);
							fclose(code_for_stream);
						}
						{ // adding index to indexes
							fprintf(indexes_stream, "[i_%d]", i);
							fflush(indexes_stream);
						}
						// encode
						fprintf(e, "%sfprintf(%s, \"[\");\n", Tabs_get(et), stream_name);
						fprintf(e, "%s%s\n", Tabs_get(et), code_for);
						Tabs_increment(et);
						// decode
						fprintf(d, "%sfscanf(%s, \"[\");\n", Tabs_get(dt), stream_name);
						fprintf(d, "%s%s\n", Tabs_get(dt), code_for);
						Tabs_increment(dt);
						//
						{
							free(code_for);
						}
					}
					attribute_printf_value(e, et, structure, attribute, indexes);
					attribute_scanf_value(d, dt, structure, attribute, indexes);
					for (int i=attribute->dimension->size-1; i>=0; i--) {
						char *string_true = (i==attribute->dimension->size-1) ? "\", \"" : "\"], \"";
						char *string_false = (i==attribute->dimension->size-1) ? "\"\"" : "\"]\"";
						// encode
						fprintf(e, "%sfprintf(%s, \"%%s\", (i_%d<%s-1)?%s:%s);\n", Tabs_get(et), stream_name, i, attribute->dimension->dimensions[i], string_true, string_false); Tabs_decrement(et);
						fprintf(e, "%s}\n", Tabs_get(et));
						// decode
						Tabs_decrement(dt);
						fprintf(d, "%s}\n", Tabs_get(dt));
						fprintf(d, "%sfscanf(%s, \"], \");\n", Tabs_get(dt), stream_name);
					}
					// encode
					fprintf(e, "%sfprintf(%s, \"]\");\n", Tabs_get(et), stream_name);
					{
						fclose(indexes_stream);
						free(indexes);
					}
					break;
				}
				default: {
					fprintf(stderr, "\'generate_json_codec_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
					exit(1);
				}
			}
			if (attribute->next != NULL) {
				fprintf(e, "%sfprintf(%s, \",\");\n", Tabs_get(et), stream_name);
				fprintf(d, "%sfscanf(%s, \",\");\n", Tabs_get(dt), stream_name);
			}
			{
				free(attribute_pointer);
				attribute_printf_value = NULL;
				attribute_scanf_value = NULL;
			}
		}
		// end
		//     encode
		fprintf(e, "%sfprintf(%s, \"\\n}\");\n", Tabs_get(et), stream_name); Tabs_decrement(et);
		fprintf(e, "%s}", Tabs_get(et));
		//     decode
		fprintf(d, "%sfscanf(%s, \"\\n}\");\n", Tabs_get(dt), stream_name); Tabs_decrement(dt);
		fprintf(d, "%s}", Tabs_get(dt));
		{
			Tabs_free(et);
			Tabs_free(dt);
			fclose(e);
			fclose(d);
			free(stream_name);
		}
	}
	char *code_json_encode;
	{
		Tabs *tabs = Tabs_create();
		size_t code_json_encode_length;
		FILE *code_json_encode_stream = open_memstream(&code_json_encode, &code_json_encode_length);
		fprintf(code_json_encode_stream, "%schar * %s_json_encode(void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(code_json_encode_stream, "%sreturn json_encode(Pointer_create(%s, structure));\n", Tabs_get(tabs), structure->name_upper); Tabs_decrement(tabs);
		fprintf(code_json_encode_stream, "%s}", Tabs_get(tabs));
		{
			Tabs_free(tabs);
			fclose(code_json_encode_stream);
		}
	}
	char *code_json_decode;
	{
		Tabs *tabs = Tabs_create();
		size_t code_json_decode_length;
		FILE *code_json_decode_stream = open_memstream(&code_json_decode, &code_json_decode_length);
		fprintf(code_json_decode_stream, "%svoid * %s_json_decode(char *structure_json) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(
			code_json_decode_stream,
			"%1$s%2$s *%3$s = (%2$s *)malloc(sizeof(%2$s));\n"
			"%1$smemset(%3$s, 0x00, sizeof(%3$s));\n"
			"%1$sreturn json_decode(structure_json, Pointer_create(%4$s, %3$s));\n",
			Tabs_get(tabs), structure->name, structure->shortcut, structure->name_upper
		); Tabs_decrement(tabs);
		fprintf(code_json_decode_stream, "%s}", Tabs_get(tabs));
		{
			Tabs_free(tabs);
			fclose(code_json_decode_stream);
		}
	}	
	char *code = string_appends(
		code_json_encode_process,
		"\n",
		code_json_decode_process,
		"\n",
		code_json_encode,
		"\n",
		code_json_decode,
		NO_MORE_STRINGS
	);
	{
		free(code_json_encode_process);
		free(code_json_decode_process);
		free(code_json_encode);
		free(code_json_decode);
	}
	return code;
}


void printf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%sfprintf(structure_json_stream, \"%s\", %s->%s%s);\n",
		Tabs_get(tabs),
		BasicType_get_by_name(attribute->data_type)->format_specifier,
		structure->shortcut, attribute->name, attribute_suffix
	);
	{
		attribute_suffix = NULL;
	}
}

void printf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%1$sstring_base64 = (%2$s->%3$s%4$s!=NULL) ? base64_encode_string(%2$s->%3$s%4$s) : base64_encode(&((Data) {3, (unsigned char *) \"\\0\\0\\0\"})) ;\n"
		"%1$sfprintf(structure_json_stream, \"\\\"%%s\\\"\", string_base64);\n"
		"%1$s{\n",
		Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix
	); Tabs_increment(tabs);
	fprintf(stream, "%sfree(string_base64);\n", Tabs_get(tabs));
	fprintf(stream, "%sstring_base64 = NULL;\n", Tabs_get(tabs)); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		attribute_suffix = NULL;
	}
}

void printf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_data_type_upper = string_to_upper(attribute->data_type);
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%1$sfprintf(structure_json_stream, \"%%s@%%lX\", \"%2$s\", (long)(void *)%3$s%4$s);\n"
		"%1$sif (%3$s%4$s!=NULL) {\n",
		Tabs_get(tabs), attribute->data_type, attribute_pointer, attribute_suffix
	); Tabs_increment(tabs);
	fprintf(stream, "%sPointerDictionary_put_by_value(pointerDictionary, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_data_type_upper, attribute_pointer, attribute_suffix); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_data_type_upper);
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}

void scanf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%sfscanf(structure_json_stream, \"%s, \", &%s->%s%s);\n", Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, structure->shortcut, attribute->name, attribute_suffix);
	{
		attribute_suffix = NULL;
	}
}

void scanf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
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
		fprintf(stream, "%sif (strcmp(\"AAAA\", string_base64)==0) {\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%s%s%s = NULL;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix);
		fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%sfree(string);\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%s%s%s = string;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
	} else {
		fprintf(stream, "%sstrcpy(%s%s, string);\n", Tabs_get(tabs), attribute_pointer, attribute_suffix);
		fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%sfree(string);\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
	}
	Tabs_decrement(tabs);
	fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%sfree(string_base64);\n", Tabs_get(tabs));
	fprintf(stream, "%sstring_base64_length = 0;\n", Tabs_get(tabs));  Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}

void scanf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_data_type_upper = string_to_upper(attribute->data_type);
	char *attribute_pointer = generate_attribute_pointer(structure, attribute);
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	
	fprintf(
		stream,
		"%1$sfscanf(structure_json_stream, \"%%*[0-9@A-Z_a-z]%%ln\", &hashCode_length);\n"
		"%1$sfseek(structure_json_stream, -hashCode_length, SEEK_CUR);\n"
		"%1$shashCode = (char *)calloc(hashCode_length+1, sizeof(char));\n"
		"%1$sfscanf(structure_json_stream, \"%%[0-9@A-Z_a-z], \", hashCode);\n"
		"%1$ssscanf(hashCode, \"%%*[^@]@%%lX\", &structure_address);\n",
		Tabs_get(tabs)
	);
	
	fprintf(stream, "%sif (structure_address==0) {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%smemset(%s%s, 0x00, sizeof(%s));\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type);
	} else {
		fprintf(stream, "%s%s%s = NULL;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix);
	}
	Tabs_decrement(tabs);
	fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%sPointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_data_type_upper, attribute_pointer, attribute_suffix);
	} else {
		fprintf(stream, "%sif (PointerDictionary_contains(pointerDictionary, hashCode)) {\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%s%s%s = (%s *) PointerDictionary_get(pointerDictionary, hashCode)->pointer;\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type); Tabs_decrement(tabs);
		fprintf(stream, "%s} else {\n", Tabs_get(tabs)); Tabs_increment(tabs);
		fprintf(stream, "%s%s%s = (%s *)malloc(sizeof(%s));\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type, attribute->data_type);
		fprintf(stream, "%smemset(%s%s, 0x00, sizeof(%s));\n", Tabs_get(tabs), attribute_pointer, attribute_suffix, attribute->data_type);
		fprintf(stream, "%sPointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_data_type_upper, attribute_pointer, attribute_suffix); Tabs_decrement(tabs);
		fprintf(stream, "%s}\n", Tabs_get(tabs));
	}
	Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%sfree(hashCode);\n", Tabs_get(tabs));
	fprintf(stream, "%shashCode_length = 0;\n", Tabs_get(tabs));
	fprintf(stream, "%sstructure_address = 0;\n", Tabs_get(tabs)); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_data_type_upper);
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}
