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
#include "c_structure_serialization/generate_source_codes/generate_json_codec.h"
#include "c_structure_serialization/generate_source_codes/generate_libraries.h"

char * generate_json_codec_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_json_encode_process(PointerDictionary *pointerDictionary, void *structure);\n", structure->name);
		fprintf(code_stream, "\n");
		fprintf(code_stream, "void %s_json_decode_process(PointerDictionary *pointerDictionary, char *structure_json, void *structure);\n", structure->name);
		fprintf(code_stream, "\n");
		fprintf(code_stream, "char * %s_json_encode(void *structure);\n", structure->name);
		fprintf(code_stream, "\n");
		fprintf(code_stream, "void * %s_json_decode(char *structure_json);", structure->name);
		fclose(code_stream);
	}
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
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		size_t code_json_encode_process_length, code_json_decode_process_length;
		FILE *e = open_memstream(&code_json_encode_process, &code_json_encode_process_length), *d = open_memstream(&code_json_decode_process, &code_json_decode_process_length);
		// start
		char *stream_name = string_appends((char *[]) {structure->shortcut, "_json_stream", NULL});
		//       encode
		fprintf(e, "%schar * %s_json_encode_process(PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(et), structure->name); Tabs_increment(et);
		fprintf(e, "%s%s *%s = (%s *) structure;\n", Tabs_get(et), structure->name, structure->shortcut, structure->name);
		fprintf(e, "%schar *%s_json;\n", Tabs_get(et), structure->shortcut);
		fprintf(e, "%s{\n", Tabs_get(et)); Tabs_increment(et);
		fprintf(e, "%ssize_t %s_json_length;\n", Tabs_get(et), structure->shortcut);
		fprintf(e, "%sFILE *%s = open_memstream(&%s_json, &%s_json_length);\n", Tabs_get(et), stream_name, structure->shortcut, structure->shortcut);
		fprintf(e, "%sfprintf(%s, \"{\\n\");\n", Tabs_get(et), stream_name);
		//       decode
		fprintf(d, "%svoid %s_json_decode_process(PointerDictionary *pointerDictionary, char *structure_json, void *structure) {\n", Tabs_get(dt), structure->name); Tabs_increment(dt);
		fprintf(d, "%s%s *%s = (%s *) structure;\n", Tabs_get(dt), structure->name, structure->shortcut, structure->name);
		fprintf(d, "%s{\n", Tabs_get(dt)); Tabs_increment(dt);
		fprintf(d, "%sFILE *%s = fmemopen(structure_json, strlen(structure_json), \"r\");\n", Tabs_get(dt), stream_name);
		fprintf(d, "%sfscanf(%s, \"{\\n\");\n", Tabs_get(dt), stream_name);
		// structure
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			char *attribute_pointer = generate_attribute_pointer(structure, attribute);
			void (*attribute_printf_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_printf_value[attribute->type];
			void (*attribute_scanf_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_scanf_value[attribute->type];
			//
			// encode
			fprintf(e, "%s// attribute \\\'%s\\\'\n", Tabs_get(et), attribute->name);
			fprintf(e, "%sfprintf(%s, \"\\t\\\"%s\\\": \");\n", Tabs_get(et), stream_name, attribute->name);
			// decode
			fprintf(d, "%s// attribute \\\'%s\\\'s\n", Tabs_get(dt), attribute->name);
			fprintf(d, "%sfscanf(%s, \"\\t\\\"%s\\\": \");\n", Tabs_get(dt), stream_name, attribute->name);
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
							char *stars_first = string_repeat_char('*', number_of_stars);
							char *stars_second = string_repeat_char('*', number_of_stars-1);
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
							fprintf(code_for_stream, "for (int i_%d=0; i_%d<%s; i_%d++) {", i, i, attribute->dimension->dimensions[i], i); // TODO: remove repeated arguments
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
						fprintf(e, "%sfprintf(%s, \"%%s\", (i_%d<%s-1)?%s:%s);\n", Tabs_get(et), stream_name, i, attribute->dimension->dimensions[i], string_true, string_false);
						Tabs_decrement(et);
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
					fprintf(stderr, "\'generate_json_codec_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRINGS[attribute->type]);
					exit(1);
				}
			}
			if (attribute->next != NULL) {
				fprintf(e, "%sfprintf(%s, \",\\n\");\n", Tabs_get(et), stream_name);
				fprintf(d, "%sfscanf(%s, \",\\n\");\n", Tabs_get(dt), stream_name);
			} else {
				fprintf(e, "%sfprintf(%s, \"\\n\");\n", Tabs_get(et), stream_name);
				fprintf(d, "%sfscanf(%s, \"\\n\");\n", Tabs_get(dt), stream_name);
			}
			{
				free(attribute_pointer);
				attribute_printf_value = NULL;
				attribute_scanf_value = NULL;
			}
		}
		// end
		//     encode
		fprintf(e, "%sfprintf(%s, \"}\");\n", Tabs_get(et), stream_name);
		fprintf(e, "%s{\n", Tabs_get(et)); Tabs_increment(et);
		fprintf(e, "%sfclose(%s);\n", Tabs_get(et), stream_name); Tabs_decrement(et);
		fprintf(e, "%s}\n", Tabs_get(et)); Tabs_decrement(et);
		fprintf(e, "%s}\n", Tabs_get(et));
		fprintf(e, "%sreturn %s_json;\n", Tabs_get(et), structure->shortcut); Tabs_decrement(et);
		fprintf(e, "%s}", Tabs_get(et));
		//     decode
		fprintf(d, "%sfprintf(%s, \"}\");\n", Tabs_get(dt), stream_name);
		fprintf(d, "%s{\n", Tabs_get(dt)); Tabs_increment(dt);
		fprintf(d, "%sfclose(%s);\n", Tabs_get(dt), stream_name); Tabs_decrement(dt);
		fprintf(d, "%s}\n", Tabs_get(dt)); Tabs_decrement(dt);
		fprintf(d, "%s}\n", Tabs_get(dt)); Tabs_decrement(dt);
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
			"%sreturn json_decode("
				"structure_json, "
				"Pointer_create("
					"%s, "
					"(%s *)malloc(sizeof(%s))"
				")"
			");\n",
			Tabs_get(tabs), structure->name_upper, structure->name, structure->name
		); Tabs_decrement(tabs);
		fprintf(code_json_decode_stream, "%s}", Tabs_get(tabs));
		{
			Tabs_free(tabs);
			fclose(code_json_decode_stream);
		}
	}	
	char *code = string_appends(
		(char *[]) {
			code_json_encode_process,
			"\n",
			code_json_decode_process,
			"\n",
			code_json_encode,
			"\n",
			code_json_decode,
			NULL
		}
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
		"%sfprintf(%s_json_stream, \"%s\", %s->%s%s);\n",
		Tabs_get(tabs), structure->shortcut,
		BasicType_get_by_name(attribute->data_type)->format_specifier,
		structure->shortcut, attribute->name, attribute_suffix
	);
	{
		attribute_suffix = NULL;
	}
}

void printf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%schar *%s_string_base64 = base64_encode_string(%s->%s%s);\n", Tabs_get(tabs), attribute->name, structure->shortcut, attribute->name, attribute_suffix);
	fprintf(stream, "%sfprintf(%s_json_stream, \"\\\"%%s\\\"\", %s_string_base64);\n", Tabs_get(tabs), structure->shortcut, attribute->name);
	fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%sfree(%s_string_base64);\n", Tabs_get(tabs), attribute->name); Tabs_decrement(tabs);
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
		"%sfprintf(%s_json_stream, \"%%s@%%lx\", \"%s\", (long)(void *)%s%s);\n",
		Tabs_get(tabs), structure->shortcut,
		attribute->data_type, attribute_pointer, attribute_suffix
	);
	fprintf(stream, "%sif (%s!=NULL) {\n", Tabs_get(tabs), attribute_pointer); Tabs_increment(tabs);
	fprintf(stream, "%sPointerDictionary_put(pointerDictionary, Pointer_create(%s, %s));\n", Tabs_get(tabs), attribute_data_type_upper, attribute_pointer); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		free(attribute_data_type_upper);
		free(attribute_pointer);
		attribute_suffix = NULL;
	}
}

void scanf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%sfscanf(%s_json_stream, \"%s, \", &%s->%s%s);\n",
		Tabs_get(tabs), structure->shortcut,
		BasicType_get_by_name(attribute->data_type)->format_specifier,
		structure->shortcut, attribute->name, attribute_suffix
	);
	{
		attribute_suffix = NULL;
	}
}

void scanf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%schar *%s_string_base64 = (char *)calloc(BASE64_LENGTH_MAX+1, sizeof(char));\n", Tabs_get(tabs), attribute->name);
	fprintf(stream, "%sfscanf(%s_json_stream, \"%%*[\\\"]%%[A-Za-z0-9+/=]s%%*[\\\"]\", %s_string_base64);\n", Tabs_get(tabs), structure->shortcut, attribute->name);
	fprintf(stream, "%sfscanf(%s_json_stream, \"\\\", \");\n", Tabs_get(tabs), structure->shortcut); // scanfing for ", " for free
	if (attribute->dimension!=NULL) {
		if (attribute->dimension->dynamic_size_source==0) {
			fprintf(stream, "%schar *%s_string = base64_decode_string(%s_string_base64);\n", Tabs_get(tabs), attribute->name, attribute->name);
			fprintf(stream, "%sstrcpy(%s->%s%s, %s_string);\n", Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix, attribute->name);
			fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
			fprintf(stream, "%sfree(%s_string);\n", Tabs_get(tabs), attribute->name); Tabs_decrement(tabs);
			fprintf(stream, "%s}\n", Tabs_get(tabs));
		} else {
			fprintf(stream, "%s%s->%s%s = base64_decode_string(%s_string_base64);\n", Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix, attribute->name);
		}
	}
	fprintf(stream, "%s{\n", Tabs_get(tabs)); Tabs_increment(tabs);
	fprintf(stream, "%sfree(%s_string_base64);\n", Tabs_get(tabs), attribute->name); Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	{
		attribute_suffix = NULL;
	}
}

void scanf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	// TODO: rework it
	fprintf(stream, "%s// TODO: add structure scanf!\n", Tabs_get(tabs));
	/*
	fprintf(stream, "%slong %s_address = 0;\n", Tabs_get(tabs), attribute->name);
	fprintf(stream, "%sfscanf(%s_json_stream, \"%%lx, \", &%s_address);\n", Tabs_get(tabs), structure->shortcut, attribute->name);
	fprintf(
		stream,
		"%s%s->%s%s = (%s%s) %s_address;\n",
		Tabs_get(tabs),
		structure->shortcut, attribute->name, attribute_suffix,
		attribute->data_type, (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY)?"":"*",
		attribute->name
	); // TODO: cant handle structure/structure_array address (
	*/
	{
		attribute_suffix = NULL;
	}
}
