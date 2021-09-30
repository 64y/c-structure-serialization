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
		fprintf(code_stream, "void * %s_json_decode_process(PointerDictionary *pointerDictionary, char *structure_json, void *structure);\n", structure->name);
		fprintf(code_stream, "\n");
		fprintf(code_stream, "char *%s_json_encode(void *structure);\n", structure->name);
		fprintf(code_stream, "\n");
		fprintf(code_stream, "char *%s_json_decode(char *structure_json);", structure->name);
		fclose(code_stream);
	}
	return code;
}


void printf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);

void printf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);

void printf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes);


char * generate_json_codec_definition(Structure *structure) {
	/*void (*array_of_printf_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		printf_primitive_value, printf_string_value, printf_structure_value, printf_structure_value,
		printf_primitive_value, printf_string_value, printf_structure_value, printf_structure_value
	};
	void (*array_of_scanf_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		scanf_primitive_value, scanf_string_value, scanf_structure_value, scanf_structure_value,
		scanf_primitive_value, scanf_string_value, scanf_structure_value, scanf_structure_value
	};*/
	char *encode, *decode;
	{
		Tabs *encode_tabs = Tabs_create(), *decode_tabs = Tabs_create();
		size_t encode_length, decode_length;
		FILE *encode_stream = open_memstream(&encode, &encode_length), *decode_stream = open_memstream(&decode, &decode_length);
				
		// start
		//       encode
		fprintf(encode_stream, "%schar * %s_json_encode(void *pointer) {\n", Tabs_get(encode_tabs), structure->name); Tabs_increment(encode_tabs);
		fprintf(encode_stream, "%s%s *%s = (%s *) pointer;\n", Tabs_get(encode_tabs), structure->name, structure->shortcut, structure->name);
		fprintf(encode_stream, "%schar *json;\n", Tabs_get(encode_tabs));
		fprintf(encode_stream, "%ssize_t json_length;\n", Tabs_get(encode_tabs));
		fprintf(encode_stream, "%sFILE *json_stream = open_memstream(&json, &json_length);\n", Tabs_get(encode_tabs));
		fprintf(encode_stream, "%sfprintf(json_stream, \"{\\n\");\n", Tabs_get(encode_tabs));
		//       decode
		fprintf(decode_stream, "%svoid * %s_json_decode(char *json) {\n", Tabs_get(decode_tabs), structure->name); Tabs_increment(decode_tabs);
		fprintf(decode_stream, "%s%s *%s = (%s *)malloc(sizeof(%s));\n", Tabs_get(decode_tabs), structure->name, structure->shortcut, structure->name, structure->name);
		fprintf(decode_stream, "%sFILE *json_stream = fmemopen(json, strlen(json), \"r\");\n", Tabs_get(decode_tabs));
		fprintf(decode_stream, "%sfscanf(json_stream, \"{\\n\");\n", Tabs_get(decode_tabs));
		// structure
		/*for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			char *attribute_pointer = generate_attribute_pointer(structure, curr);
			void (*printf_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_printf_value[curr->type];
			void (*scanf_value) (FILE *, Tabs *, Structure *, Attribute *, char *) = array_of_scanf_value[curr->type];
			//
			// encode
			fprintf(encode_stream, "%s// attribute \\\'%s\\\'\n", Tabs_get(encode_tabs), curr->name);
			fprintf(encode_stream, "%sfprintf(json_stream, \"\\t\\\"%s\\\": \");\n", Tabs_get(encode_tabs), curr->name);
			// decode
			fprintf(decode_stream, "%s// attribute \\\'%s\\\'s\n", Tabs_get(decode_tabs), curr->name);
			fprintf(decode_stream, "%sfscanf(json_stream, \"\\t\\\"%s\\\": \");\n", Tabs_get(decode_tabs), curr->name);
			switch (curr->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					printf_value(encode_stream, encode_tabs, structure, curr, NULL);
					scanf_value(decode_stream, decode_tabs, structure, curr, NULL);
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					char *code_for;
					char *indexes;
					size_t indexes_length;
					FILE *indexes_stream = open_memstream(&indexes, &indexes_length);
					fprintf(indexes_stream, "%s", "");
					fflush(indexes_stream);
					
					int cddsc = curr->dimension->dynamic_size_source + (curr->type==STRUCTURE_POINTER_ARRAY);
					for (int i=0; i<curr->dimension->size; i++) {
						// decode
						if (i>=curr->dimension->static_size_source) {
							char *stars_first = string_repeat_char('*', cddsc);
							char *stars_second = string_repeat_char('*', cddsc-1);
							fprintf(
								decode_stream,
								"%s%s%s = (%s%s)calloc(%s->%s, sizeof(%s%s));\n",
								Tabs_get(decode_tabs),
								attribute_pointer, indexes,
								curr->data_type, stars_first,
								structure->shortcut, curr->dimension->dimensions[i],
								curr->data_type, stars_second
							);
							{
								free(stars_first);
								free(stars_second);
							}
							cddsc = cddsc - 1;
						}
						//
						{	// creating for here
							size_t code_for_length;
							FILE *code_for_stream = open_memstream(&code_for, &code_for_length);
							if (i < curr->dimension->static_size) {
								fprintf(code_for_stream, "for (int i_%d=0; i_%d<%s; i_%d++) {", i, i, curr->dimension->dimensions[i], i);
							} else {
								fprintf(code_for_stream, "for (int i_%d=0; i_%d<%s->%s; i_%d++) {", i, i, structure->shortcut, curr->dimension->dimensions[i], i);
							}
							fclose(code_for_stream);
						}
						{ // adding index to indexes
							fprintf(indexes_stream, "[i_%d]", i);
							fflush(indexes_stream);
						}
						// encode
						fprintf(encode_stream, "%sfprintf(json_stream, \"[\");\n", Tabs_get(encode_tabs));
						fprintf(encode_stream, "%s%s\n", Tabs_get(encode_tabs), code_for);
						Tabs_increment(encode_tabs);
						// decode
						fprintf(decode_stream, "%sfscanf(json_stream, \"[\");\n", Tabs_get(decode_tabs));
						fprintf(decode_stream, "%s%s\n", Tabs_get(decode_tabs), code_for);
						Tabs_increment(decode_tabs);
						//
						{
							free(code_for);
						}
					}
					printf_value(encode_stream, encode_tabs, structure, curr, indexes);
					scanf_value(decode_stream, decode_tabs, structure, curr, indexes);
					for (int i=curr->dimension->size-1; i>=0; i--) {
						char *string_true = (i==curr->dimension->size-1) ? "\", \"" : "\"], \"";
						char *string_false = (i==curr->dimension->size-1) ? "\"\"" : "\"]\"";
						// encode
						if (i < curr->dimension->static_size) { // only static sizes
							fprintf(encode_stream, "%sfprintf(json_stream, \"%%s\", (i_%d<%s-1)?%s:%s);\n", Tabs_get(encode_tabs), i, curr->dimension->dimensions[i], string_true, string_false);
						} else {
							fprintf(encode_stream, "%sfprintf(json_stream, \"%%s\", (i_%d<%s->%s-1)?%s:%s);\n", Tabs_get(encode_tabs), i, structure->shortcut, curr->dimension->dimensions[i], string_true, string_false);
						}
						Tabs_decrement(encode_tabs);
						fprintf(encode_stream, "%s}\n", Tabs_get(encode_tabs));
						// decode
						Tabs_decrement(decode_tabs);
						fprintf(decode_stream, "%s}\n", Tabs_get(decode_tabs));
						fprintf(decode_stream, "%sfscanf(json_stream, \"], \");\n", Tabs_get(decode_tabs));
					}
					// encode
					fprintf(encode_stream, "%sfprintf(json_stream, \"]\");\n", Tabs_get(encode_tabs));
					{
						fclose(indexes_stream);
						free(indexes);
					}
					break;
				}
				default: {
					printf("Can\'t work with %s!\n", ATTRIBUTE_TYPE_STRINGS[curr->type]);
				}
			}
			if (curr->next != NULL) {
				fprintf(encode_stream, "%sfprintf(json_stream, \",\\n\");\n", Tabs_get(encode_tabs));
				fprintf(decode_stream, "%sfscanf(json_stream, \",\\n\");\n", Tabs_get(decode_tabs));
			} else {
				fprintf(encode_stream, "%sfprintf(json_stream, \"\\n\");\n", Tabs_get(encode_tabs));
				fprintf(decode_stream, "%sfscanf(json_stream, \"\\n\");\n", Tabs_get(decode_tabs));
			}
			{
				free(attribute_pointer);
				printf_value = NULL;
				scanf_value = NULL;
			}
		}*/
		// end
		//     encode
		fprintf(encode_stream, "%sfprintf(json_stream, \"}\");\n", Tabs_get(encode_tabs));
		fprintf(encode_stream, "%sfclose(json_stream);\n", Tabs_get(encode_tabs));
		fprintf(encode_stream, "%sreturn json;\n", Tabs_get(encode_tabs));	Tabs_decrement(encode_tabs);
		fprintf(encode_stream, "%s}", Tabs_get(encode_tabs));
		//     decode
		fprintf(decode_stream, "%sfscanf(json_stream, \"}\");\n", Tabs_get(decode_tabs));
		fprintf(decode_stream, "%sfclose(json_stream);\n", Tabs_get(decode_tabs));
		fprintf(decode_stream, "%sreturn %s;\n", Tabs_get(decode_tabs), structure->shortcut);	Tabs_decrement(decode_tabs);
		fprintf(decode_stream, "%s}", Tabs_get(decode_tabs));
		
		{
			Tabs_free(encode_tabs);
			fclose(encode_stream);
			Tabs_free(decode_tabs);
			fclose(decode_stream);
		}
	}
	char *code = string_appends((char *[]) {encode, "\n\n", decode, NULL});
	{
		free(encode);
		free(decode);
	}
	return code;
}


void printf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%sfprintf(json_stream, \"%s\", %s->%s%s);\n",
		Tabs_get(tabs),
		BasicType_get_by_name(attribute->data_type)->format_specifier,
		structure->shortcut, attribute->name, attribute_suffix
	);
	attribute_suffix = NULL;
}

void scanf_primitive_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%sfscanf(json_stream, \"%s, \", &%s->%s%s);\n", // scanfing for ", " for free
		Tabs_get(tabs),
		BasicType_get_by_name(attribute->data_type)->format_specifier,
		structure->shortcut, attribute->name, attribute_suffix
	);
	attribute_suffix = NULL;
}

void printf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%schar *%s_json = base64_encode_string(%s->%s%s);\n", Tabs_get(tabs), attribute->name, structure->shortcut, attribute->name, attribute_suffix);
	fprintf(stream, "%sfprintf(json_stream, \"\\\"%%s\\\"\", %s_json);\n", Tabs_get(tabs), attribute->name);
	fprintf(stream, "%sfree(%s_json);\n", Tabs_get(tabs), attribute->name);
	attribute_suffix = NULL;
}

void scanf_string_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(stream, "%schar *%s_json = (char *)calloc(JSON_LENGTH_MAX+1, sizeof(char));\n", Tabs_get(tabs), attribute->name);
	fprintf(stream, "%sfscanf(json_stream, \"%%*[\\\"]%%[A-Za-z0-9+/=]s%%*[\\\"]\", %s_json);\n", Tabs_get(tabs), attribute->name);
	fprintf(stream, "%sfscanf(json_stream, \"\\\", \");\n", Tabs_get(tabs)); // scanfing for ", " for free
	if (attribute->dimension!=NULL && attribute->dimension->dynamic_size_source==0) {
		fprintf(stream, "%schar *%s_string = base64_decode_string(%s_json);\n", Tabs_get(tabs), attribute->name, attribute->name);
		fprintf(stream, "%sstrcpy(%s->%s%s, %s_string);\n", Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix, attribute->name);
		fprintf(stream, "%sfree(%s_string);\n", Tabs_get(tabs), attribute->name);
	} else {
		fprintf(stream, "%s%s->%s%s = base64_decode_string(%s_json);\n", Tabs_get(tabs), structure->shortcut, attribute->name, attribute_suffix, attribute->name);
	}
	fprintf(stream, "%sfree(%s_json);\n", Tabs_get(tabs), attribute->name);
	attribute_suffix = NULL;
}

void printf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	fprintf(
		stream,
		"%sfprintf(json_stream, \"%%lx\", (long)(void *)%s%s->%s%s);\n",
		Tabs_get(tabs),
		(attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY)?"&":"",
		structure->shortcut, attribute->name, attribute_suffix
	);
	attribute_suffix = NULL;
}

void scanf_structure_value(FILE *stream, Tabs *tabs, Structure *structure, Attribute *attribute, char *indexes) {
	char *attribute_suffix = (indexes==NULL)?"":indexes;
	
	fprintf(stream, "%slong %s_address = 0;\n", Tabs_get(tabs), attribute->name);
	fprintf(stream, "%sfscanf(json_stream, \"%%lx, \", &%s_address);\n", Tabs_get(tabs), attribute->name);
	fprintf(
		stream,
		"%s%s->%s%s = (%s%s) %s_address;\n",
		Tabs_get(tabs),
		structure->shortcut, attribute->name, attribute_suffix,
		attribute->data_type, (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY)?"":"*",
		attribute->name
	); // TODO: cant handle structure/structure_array address (
	attribute_suffix = NULL;
}
