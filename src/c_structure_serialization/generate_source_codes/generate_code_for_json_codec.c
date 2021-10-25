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
		"%1$svoid %2$s_json_encode_process(FILE *structure_json_stream, PointerSet *pointerSet, Pointer *pointer);\n"
		"%1$svoid %2$s_json_decode_process(FILE *structure_json_stream, PointerSet *pointerSet, Pointer *pointer);",
		Tabs_get(tabs), structure->name
	);
}

void generate_json_codec_definition(FILE *c_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		c_stream,
		"%1$schar * %3$s_json_encode(void *structure) {\n"
		"%1$s%2$sData *data = encode(JSON_ENCODE, Pointer_create_by_name_pointer(%4$s, structure));\n"
		"%1$s%2$schar *structure_json = data->bytes;\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sdata->bytes_size = 0;\n"
		"%1$s%2$s%2$sfree(data);\n"
		"%1$s%2$s%2$sdata = NULL;\n"
		"%1$s%2$s}\n"
		"%1$s%2$sreturn structure_json;\n"
		"%1$s}\n"
		"%1$s\n"
		"%1$svoid * %3$s_json_decode(char *structure_json) {\n"
		"%1$s%2$s%3$s *%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$ssize_t structure_hashCode_length = 0;\n"
		"%1$s%2$ssscanf(structure_json+1, \"%%*[$0-9@A-Z_a-z]%%ln\", &structure_hashCode_length);\n"
		"%1$s%2$schar *structure_hashCode = (char *)calloc(structure_hashCode_length+1, sizeof(char));\n"
		"%1$s%2$ssscanf(structure_json+1, \"%%[$0-9@A-Z_a-z]\", structure_hashCode);\n"
		"%1$s%2$svoid *structure = decode(\n"
		"%1$s%2$s%2$sJSON_DECODE,\n"
		"%1$s%2$s%2$sPointer_create_by_name_pointer_hashCode(%4$s, %5$s, structure_hashCode),\n"
		"%1$s%2$s%2$s&((Data) {strlen(structure_json), (byte *) structure_json})\n"
		"%1$s%2$s);\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sfree(structure_hashCode);\n"
		"%1$s%2$s%2$sstructure_hashCode = NULL;\n"
		"%1$s%2$s%2$sstructure_hashCode_length = 0;\n"
		"%1$s%2$s}\n"
		"%1$s%2$sreturn structure;\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper, structure->shortcut
	);
	// json_XXcode_process
	void (*json_encode_methods[]) (FILE *, Tabs *, Attribute *, char *) = { NULL,
		json_encode_primitive, json_encode_string, json_encode_structure, json_encode_structure,
		json_encode_primitive, json_encode_string, json_encode_structure, json_encode_structure
	};
	void (*json_decode_methods[]) (FILE *, Tabs *, Attribute *, char *) = { NULL,
		json_decode_primitive, json_decode_string, json_decode_structure, json_decode_structure_pointer,
		json_decode_primitive, json_decode_string, json_decode_structure, json_decode_structure_pointer
	};
	char *code_json_encode_process, *code_json_decode_process;
	{
		size_t code_json_encode_process_length, code_json_decode_process_length;
		FILE *e = open_memstream(&code_json_encode_process, &code_json_encode_process_length), *d = open_memstream(&code_json_decode_process, &code_json_decode_process_length);
		
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		// start
		char *stream_name = string_create("structure_json_stream");

		//       encode
		fprintf(e, "%svoid %s_json_encode_process(FILE *structure_json_stream, PointerSet *pointerSet, Pointer *pointer) {\n", Tabs_get(et), structure->name); Tabs_increment(et);
		// fprintf(e, "%sif (poiner==NULL) return;\n", Tabs_get(et));
		//       decode
		fprintf(d, "%svoid %s_json_decode_process(FILE *structure_json_stream, PointerSet *pointerSet, Pointer *pointer) {\n", Tabs_get(dt), structure->name); Tabs_increment(dt);
		// fprintf(d, "%sif (structure==NULL) return;\n", Tabs_get(et));
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
		//if (Structure_contains_structure_attributes(structure)) {
			//encode
			//decode
			fprintf(
				d,
				"%1$schar *structure_hashCode;\n"
				"%1$ssize_t structure_hashCode_length;\n"
				"%1$slong structure_address;\n",
				Tabs_get(dt)
			);
		//}
		//
		//       encode
		fprintf(
			e,
			"%1$s%2$s *%3$s = (%4$s *) pointer->pointer;\n"
			"%1$sfprintf(structure_json_stream, \"\\\"%%s\\\": {\", pointer->hashCode);\n",
			Tabs_get(et), structure->name, structure->shortcut, structure->name
		);
		//       decode
		fprintf(
			d,
			"%1$s%3$s *%4$s = (%5$s *) pointer->pointer;\n"
			"%1$sfscanf(structure_json_stream, \"\\\"%%*[^\\\"]%%ln\", &structure_hashCode_length);\n"
			"%1$sfseek(structure_json_stream, -structure_hashCode_length, SEEK_CUR);\n"
			"%1$sstructure_hashCode = (char *)calloc(-1+structure_hashCode_length+1, sizeof(char));\n"
			"%1$sfscanf(structure_json_stream, \"\\\"%%[^\\\"]\\\": {\", structure_hashCode);\n"
			"%1$sif (strcmp(structure_hashCode, pointer->hashCode)==0) {\n"
			"%1$s%2$sfree(structure_hashCode);\n"
			"%1$s%2$sstructure_hashCode = NULL;\n"
			"%1$s%2$sstructure_hashCode_length = 0;\n"
			"%1$s} else {\n"
			"%1$s%2$sfprintf(stderr, \"Wrong order of element \\\'%%s\\\'!=\\\'%%s\\\'!\\n\", structure_hashCode, pointer->hashCode);\n"
			"%1$s%2$sexit(1);\n"
			"%1$s}\n",
			Tabs_get(dt), Tabs_get_tab(tabs), structure->name, structure->shortcut, structure->name
		);
		// structure
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			void (*json_encode_method) (FILE *, Tabs *, Attribute *, char *) = json_encode_methods[attribute->type];
			void (*json_decode_method) (FILE *, Tabs *, Attribute *, char *) = json_decode_methods[attribute->type];
			// encode
			fprintf(
				e,
				"%1$s// attribute \\\'%2$s\\\'\n"
				"%1$sfprintf(structure_json_stream, \"\\n\\t\\\"%2$s\\\": \");\n",
				Tabs_get(et), attribute->name
			);
			// decode
			fprintf(
				d,
				"%1$s// attribute \\\'%2$s\\\'s\n"
				"%1$sfscanf(structure_json_stream, \"\\n\\t\\\"%2$s\\\": \");\n",
				Tabs_get(dt), attribute->name
			);
			//
			switch (attribute->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					char *attribute_pointer = generate_attribute_pointer(structure, attribute, NULL);
					json_encode_method(e, et, attribute, attribute_pointer);
					json_decode_method(d, dt, attribute, attribute_pointer);
					{
						string_free(attribute_pointer);
					}
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					char *attribute_pointer, *code_for, *code_indexes;
					FILE *code_indexes_stream;
					{
						size_t code_indexes_length;
						code_indexes_stream = open_memstream(&code_indexes, &code_indexes_length);
						fprintf(code_indexes_stream, "%s", "");
						fflush(code_indexes_stream);
					}
					
					int number_of_stars = attribute->dimension->dynamic_size_source + (attribute->type==STRUCTURE_POINTER_ARRAY);
					for (int i=0; i<attribute->dimension->size; i++) {
						// decode
						if (i>=attribute->dimension->static_size_source) {
							attribute_pointer = generate_attribute_pointer(structure, attribute, code_indexes);
							char *stars_first = string_repeat_star(number_of_stars);
							char *stars_second = string_repeat_star(number_of_stars-1);
							fprintf(
								d,
								"%s%s = (%s%s)calloc(%s, sizeof(%s%s));\n",
								Tabs_get(dt),
								attribute_pointer,
								attribute->data_type, stars_first,
								attribute->dimension->dimensions[i],
								attribute->data_type, stars_second
							);
							{
								free(attribute_pointer);
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
							fprintf(code_indexes_stream, "[i_%d]", i);
							fflush(code_indexes_stream);
						}
						// encode
						fprintf(
							e,
							"%1$sfprintf(structure_json_stream, \"[\");\n"
							"%1$s%2$s\n",
							Tabs_get(et), code_for
						); Tabs_increment(et);
						// decode
						fprintf(
							d,
							"%1$sfscanf(structure_json_stream, \"[\");\n"
							"%1$s%2$s\n",
							Tabs_get(dt), code_for
						); Tabs_increment(dt);
						//
						{
							free(code_for);
						}
					}
					attribute_pointer = generate_attribute_pointer(structure, attribute, code_indexes);
					json_encode_method(e, et, attribute, attribute_pointer);
					json_decode_method(d, dt, attribute, attribute_pointer);
					for (int i=attribute->dimension->size-1; i>=0; i--) {
						char *string_true = (i==attribute->dimension->size-1) ? "\", \"" : "\"], \"";
						char *string_false = (i==attribute->dimension->size-1) ? "\"\"" : "\"]\"";
						// encode
						fprintf(e, "%sfprintf(structure_json_stream, \"%%s\", (i_%d<%s-1)?%s:%s);\n", Tabs_get(et), i, attribute->dimension->dimensions[i], string_true, string_false); Tabs_decrement(et);
						fprintf(e, "%s}\n", Tabs_get(et));
						// decode
						Tabs_decrement(dt);
						fprintf(d, "%s}\n", Tabs_get(dt));
						fprintf(d, "%sfscanf(structure_json_stream, \"], \");\n", Tabs_get(dt));
					}
					// encode
					fprintf(e, "%sfprintf(structure_json_stream, \"]\");\n", Tabs_get(et));
					{
						string_free(attribute_pointer);
						fclose(code_indexes_stream);
						string_free(code_indexes);
					}
					break;
				}
				default: {
					fprintf(stderr, "\'generate_json_codec_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
					exit(1);
				}
			}
			if (attribute->next != NULL) {
				fprintf(e, "%sfprintf(structure_json_stream, \",\");\n", Tabs_get(et));
				fprintf(d, "%sfscanf(structure_json_stream, \",\");\n", Tabs_get(dt));
			}
		}
		// end
		//     encode
		fprintf(e, "%sfprintf(structure_json_stream, \"\\n}%%s\", (pointer->next!=NULL)?\",\\n\":\"\");\n", Tabs_get(et)); Tabs_decrement(et);
		fprintf(e, "%s}", Tabs_get(et));
		//     decode
		fprintf(d, "%sfscanf(structure_json_stream, \"\\n},\\n\");\n", Tabs_get(dt)); Tabs_decrement(dt);
		fprintf(d, "%s}", Tabs_get(dt));
		{
			Tabs_free(et);
			Tabs_free(dt);
			fclose(e);
			fclose(d);
			free(stream_name);
		}
	}
	fprintf(c_stream, "\n%s\n\n%s", code_json_encode_process, code_json_decode_process);
	{
		free(code_json_encode_process);
		free(code_json_decode_process);
	}
}

void json_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_json_stream, \"%s\", %s);\n",
		Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, attribute_pointer
	);
}

void json_encode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
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

void json_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfprintf(structure_json_stream, \"%%s@%%lX\", \"%s\", (long)(void *)%s);\n",
		Tabs_get(tabs), attribute->data_type, attribute_pointer
	);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%s, %s));\n", Tabs_get(tabs), attribute->data_type_upper, attribute_pointer);
	} else {
		fprintf(stream, "%1$sif (%4$s!=NULL) {\n%1$s%2$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%3$s, %4$s));\n%1$s}", Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer);
	}
}

void json_decode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfscanf(structure_json_stream, \"%s, \", &%s);\n",
		Tabs_get(tabs), BasicType_get_by_name(attribute->data_type)->format_specifier, attribute_pointer
	);
}

void json_decode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
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

void json_decode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sfscanf(structure_json_stream, \"%%*[$0-9@A-Z_a-z]%%ln\", &structure_hashCode_length);\n"
		"%1$sfseek(structure_json_stream, -structure_hashCode_length, SEEK_CUR);\n"
		"%1$sstructure_hashCode = (char *)calloc(structure_hashCode_length+1, sizeof(char));\n"
		"%1$sfscanf(structure_json_stream, \"%%[$0-9@A-Z_a-z], \", structure_hashCode);\n"
		"%1$ssscanf(structure_hashCode, \"%%*[^@]@%%lX\", &structure_address);\n"
		"%1$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer_hashCode(%3$s, %4$s, structure_hashCode));\n"
		"%1$s{\n"
		"%1$s%2$sfree(structure_hashCode);\n"
		"%1$s%2$sstructure_hashCode = NULL;\n"
		"%1$s%2$sstructure_hashCode_length = 0;\n"
		"%1$s%2$sstructure_address = 0;\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer
	);
}

void json_decode_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sfscanf(structure_json_stream, \"%%*[$0-9@A-Z_a-z]%%ln\", &structure_hashCode_length);\n"
		"%1$sfseek(structure_json_stream, -structure_hashCode_length, SEEK_CUR);\n"
		"%1$sstructure_hashCode = (char *)calloc(structure_hashCode_length+1, sizeof(char));\n"
		"%1$sfscanf(structure_json_stream, \"%%[$0-9@A-Z_a-z], \", structure_hashCode);\n"
		"%1$ssscanf(structure_hashCode, \"%%*[^@]@%%lX\", &structure_address);\n"
		"%1$sif(structure_address==0) {\n"
		"%1$s%2$s%5$s = NULL;\n"
		"%1$s} else {\n"
		"%1$s%2$sif (PointerSet_contains_by_hashCode(pointerSet, structure_hashCode)) {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *) PointerSet_get_by_hashCode(pointerSet, structure_hashCode);\n"
		"%1$s%2$s} else {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$s%2$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer_hashCode(%4$s, %5$s, structure_hashCode));\n"
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
