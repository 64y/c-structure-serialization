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
#include "c_structure_serialization/generate_source_codes/generate_attribute.h"
#include "c_structure_serialization/generate_source_codes/generate_json_codec.h"


char * generate_json_codec_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_json_encode(void *pointer);", structure->name);
		fprintf(code_stream, "void * %s_json_decode(char *json);", structure->name);
		fclose(code_stream);
	}
	return code;
}
/* TODO:
void printf_primitive(FILE *stream, Tabs* tabs, Structure *structure, Attribute *attribute, char *indexes);
void printf_string(FILE *stream, Tabs* tabs, Structure *structure, Attribute *attribute, char *indexes);
void printf_structure(FILE *stream, Tabs* tabs, Structure *structure, Attribute *attribute, char *indexes);

void scanf_primitive(FILE *stream, Tabs* tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_string(FILE *stream, Tabs* tabs, Structure *structure, Attribute *attribute, char *indexes);
void scanf_structure(FILE *stream, Tabs* tabs, Structure *structure, Attribute *attribute, char *indexes);
*/

char * generate_json_codec_definition(Structure *structure) {
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
		for (Attribute *curr=structure->head; curr!=NULL; curr=curr->next) {
			char *attribute_pointer = generate_attribute_pointer(structure, curr);
			// encode
			fprintf(encode_stream, "%s// %s\n", Tabs_get(encode_tabs), curr->name);
			// decode
			fprintf(decode_stream, "%s// %s\n", Tabs_get(decode_tabs), curr->name);
			switch (curr->type) {
				case PRIMITIVE: {
					char *format; {
						size_t format_length;
						FILE *format_stream = open_memstream(&format, &format_length);
						fprintf(format_stream, "\"\\t\\\"%s\\\": %s\"", curr->name, get_basic_type_by_name(curr->data_type)->format_specifier);
						{
							fclose(format_stream);
						}
					}
					// encode
					fprintf(encode_stream, "%sfprintf(json_stream, %s, %s);\n", Tabs_get(encode_tabs), format, attribute_pointer);
					// decode
					fprintf(decode_stream, "%sfscanf(json_stream, %s, &%s);\n", Tabs_get(encode_tabs), format, attribute_pointer);
					{
						free(format);
					}
					break;
				}
				case STRING: {
					// encode
					fprintf(encode_stream, "%schar *%s_json = base64_encode_string(%s);\n", Tabs_get(encode_tabs), curr->name, attribute_pointer);
					fprintf(encode_stream, "%sfprintf(json_stream, \"\\t\\\"%s\\\": \\\"%%s\\\"\", %s_json);\n", Tabs_get(encode_tabs), curr->name, curr->name);
					fprintf(encode_stream, "%sfree(%s_json);\n", Tabs_get(encode_tabs), curr->name);
					// decode
					fprintf(decode_stream, "%schar *%s_json = (char *)calloc(JSON_LENGTH_MAX+1, sizeof(char));\n", Tabs_get(decode_tabs), curr->name);
					fprintf(decode_stream, "%sfscanf(json_stream, \"\\t\\\"%s\\\": %%*[\\\"]%%[A-Za-z0-9+/=]s%%*[\\\"]\", %s_json);\n", Tabs_get(decode_tabs), curr->name, curr->name);
					fprintf(decode_stream, "%sfscanf(json_stream, \"\\\"\");\n", Tabs_get(decode_tabs));
					fprintf(decode_stream, "%s%s = base64_decode_string(%s_json);\n", Tabs_get(decode_tabs), attribute_pointer, curr->name);
					fprintf(decode_stream, "%sfree(%s_json);\n", Tabs_get(encode_tabs), curr->name);
					break;
				}
				case PRIMITIVE_ARRAY: {
					// encode 
					fprintf(encode_stream, "%sfprintf(json_stream, \"\\t\\\"%s\\\": \");\n", Tabs_get(encode_tabs), curr->name);
					// decode
					fprintf(decode_stream, "%sfscanf(json_stream, \"\\t\\\"%s\\\": \");\n", Tabs_get(decode_tabs), curr->name);
					//
					
					char *code_for;
					char *indexes;
					size_t indexes_length;
					FILE *indexes_stream = open_memstream(&indexes, &indexes_length);
					fprintf(indexes_stream, "%s", "");
					fflush(indexes_stream);
					
					for (int i=0, cddsc=curr->dimension->dynamic_size_source; i<curr->dimension->size; i++) {
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
						{
							size_t code_for_length;
							FILE *code_for_stream = open_memstream(&code_for, &code_for_length);
							if (i < curr->dimension->static_size) {
								fprintf(code_for_stream, "for (int i_%d=0; i_%d<%s; i_%d++) {", i, i, curr->dimension->dimensions[i], i);
							} else {
								fprintf(code_for_stream, "for (int i_%d=0; i_%d<%s->%s; i_%d++) {", i, i, structure->shortcut, curr->dimension->dimensions[i], i);
							}
							fclose(code_for_stream);
						}
						{
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
					}
					// encode
					fprintf(encode_stream, "%sfprintf(json_stream, \"%s\", %s%s);\n", Tabs_get(encode_tabs), get_basic_type_by_name(curr->data_type)->format_specifier, attribute_pointer, indexes);
					// decode
					fprintf(decode_stream, "%sfscanf(json_stream, \"%s, \", &%s%s);\n", Tabs_get(encode_tabs), get_basic_type_by_name(curr->data_type)->format_specifier, attribute_pointer, indexes);
					
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
			}
		}
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

