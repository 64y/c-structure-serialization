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
			switch (curr->type) {
				case PRIMITIVE: {
					char *format; {
						size_t format_length;
						FILE *format_stream = open_memstream(&format, &format_length);
						fprintf(format_stream, "\"\t\\\"%s\\\": %s%s\\n\"", curr->name, get_basic_type_by_name(curr->data_type)->format_specifier, (curr->next!=NULL)?",":"");
						{
							fclose(format_stream);
						}
					}
					// encode
					fprintf(encode_stream, "%sfprintf(json_stream, %s, %s);\n", Tabs_get(encode_tabs), format, attribute_pointer);
					// decode
					fprintf(decode_stream, "%sfscanf(json_stream, %s, &%s);\n", Tabs_get(encode_tabs), format, attribute_pointer);
					break;
				}
				default: {
					printf("Can\'t work with %s!\n", ATTRIBUTE_TYPE_STRINGS[curr->type]);
				}
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

