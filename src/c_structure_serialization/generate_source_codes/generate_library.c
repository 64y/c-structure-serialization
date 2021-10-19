#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "c_structure_serialization/utils/array.h"
#include "c_structure_serialization/utils/strings.h"
#include "c_structure_serialization/utils/files.h"
#include "c_structure_serialization/data_types/dimension.h"
#include "c_structure_serialization/data_types/attribute.h"
#include "c_structure_serialization/data_types/structure.h"
#include "c_structure_serialization/data_types/structure_regular_expressions.h"
#include "c_structure_serialization/generate_source_codes/generate_library.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute, char *indexes) {
	char *pointer;
	{
		size_t pointer_length;
		FILE *pointer_stream = open_memstream(&pointer, &pointer_length);
		if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
			fprintf(pointer_stream, "&");
		}
		fprintf(pointer_stream, "%s->%s", structure->shortcut, attribute->name);
		if (indexes!=NULL) {
			fprintf(pointer_stream, "%s", indexes);
		}
		fclose(pointer_stream);
	}
	return pointer;
}


void generate_library_source_code_for_structure(char *path_to_sources, Structure *structure) {
	
}
	/*char *path_libraries = string_appends(project_path, "/libraries", NO_MORE_STRINGS);
	mkdir(path_libraries, 0777);
	char *structure_library_h_file_name = string_appends(path_libraries, "/", structure->name_lower, "_library.h", NO_MORE_STRINGS);
	char *structure_library_c_file_name = string_appends(path_libraries, "/", structure->name_lower, "_library.c", NO_MORE_STRINGS);
	char *code_h;
	{
		size_t generate_code_size = 3;
		char * (*generate_code[]) (Structure *structure) = {
			generate_to_string_method_declaration,
			generate_json_codec_declaration,
			generate_byte_codec_declaration
		};
		
		size_t code_h_length;
		FILE *code_h_stream = open_memstream(&code_h, &code_h_length);
		fprintf(code_h_stream, "#ifndef %s_LIBRARY_H\n", structure->name_upper);
		fprintf(code_h_stream, "#define %s_LIBRARY_H\n", structure->name_upper);
		fprintf(code_h_stream, "\n");
		fprintf(code_h_stream, "#include \"includes.h\"\n");
		fprintf(code_h_stream, "\n");
		for (int i=0; i<generate_code_size; i++) {
			char *code = generate_code[i](structure);
			fprintf(code_h_stream, "%s\n\n", code);
			free(code);
		}
		fprintf(code_h_stream, "#endif");
		{
			fclose(code_h_stream);
		}
	}
	file_write(structure_library_h_file_name, code_h);
	char *code_c;
	{
		size_t generate_code_size = 3;
		char * (*generate_code[]) (Structure *structure) = {
			generate_to_string_method_definition,
			generate_json_codec_definition,
			generate_byte_codec_definition
		};
		
		size_t code_c_length;
		FILE *code_c_stream = open_memstream(&code_c, &code_c_length);
		fprintf(code_c_stream, "#include \"includes.h\"\n");
		for (int i=0; i<generate_code_size; i++) {
			char *code = generate_code[i](structure);
			fprintf(code_c_stream, "\n\n%s", code);
			free(code);
		}
		{
			fclose(code_c_stream);
		}
	}
	file_write(structure_library_c_file_name, code_c);
	{
		free(path_libraries);
		free(structure_library_h_file_name);
		free(structure_library_c_file_name);
		free(code_h);
		free(code_c);
	}*/
/*
// TO_STRING
	void (*printf_methods[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL, 
		printf_primitive, printf_primitive, printf_structure, printf_structure,
		printf_primitive, printf_primitive, printf_structure, printf_structure
	};
	char *code_structure_to_string_process;
	{
		size_t code_structure_to_string_process_length;
		FILE *s = open_memstream(&code_structure_to_string_process, &code_structure_to_string_process_length);
		
		Tabs *tabs = Tabs_create();
		
		char *stream_name = string_create("structure_string_stream");
		fprintf(s, "%svoid %s_to_string_process(FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(s, "%s%s *%s = (%s *) structure;\n", Tabs_get(tabs), structure->name, structure->shortcut, structure->name);
		//
		if (Structure_contains_array_attributes(structure)) {
			fprintf(s, "%sBoolean is_last_element_in_array = false;\n", Tabs_get(tabs));
		}
		fprintf(s, "%sfprintf(%s, \"%%s@%%lX\", \"%s\", (long)(void *) %s);\n", Tabs_get(tabs), stream_name, structure->name, structure->shortcut);
		fprintf(s, "%sif (%s != NULL) {\n", Tabs_get(tabs), structure->shortcut); Tabs_increment(tabs);
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			fprintf(s, "%s// %s->%s\n", Tabs_get(tabs), structure->shortcut, attribute->name);
			fprintf(s, "%sfprintf(%s, \"\\n%%s: \", \"%s\");\n", Tabs_get(tabs), stream_name, attribute->name);
			switch (attribute->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					printf_methods[attribute->type](s, tabs, structure, attribute, "");
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					fprintf(s, "%sfprintf(%s, \"\\n\");\n", Tabs_get(tabs), stream_name);
					fprintf(s, "%sis_last_element_in_array = false;\n", Tabs_get(tabs));
					char *code_loop, *code_indexes, *code_is_last;
					{
						size_t code_loop_length, code_indexes_length, code_is_last_length;
						FILE *code_loop_stream=open_memstream(&code_loop, &code_loop_length), *code_indexes_stream=open_memstream(&code_indexes, &code_indexes_length), *code_is_last_stream=open_memstream(&code_is_last, &code_is_last_length);
						for (int i=0; i<attribute->dimension->size; i++) {
							fprintf(code_loop_stream, "%sfor (int i_%d=0; i_%d<%s; i_%d++) {\n", Tabs_get(tabs), i, i, attribute->dimension->dimensions[i], i);
							fprintf(code_indexes_stream, "[i_%d]", i);
							fprintf(code_is_last_stream, "i_%d==%s-1%s", i, attribute->dimension->dimensions[i], (i<attribute->dimension->size-1)?" &&":"");
							Tabs_increment(tabs);
						}
						{
							fclose(code_loop_stream);
							fclose(code_indexes_stream);
							fclose(code_is_last_stream);
						}
					}
					fprintf(s, "%s", code_loop);
					printf_methods[attribute->type](s, tabs, structure, attribute, code_indexes);
					fprintf(s, "%sfprintf(%s, \"%%s\", (i_%ld<%s-1)?\", \":\"\");\n", Tabs_get(tabs), stream_name, attribute->dimension->size-1, attribute->dimension->dimensions[attribute->dimension->size-1]);
					fprintf(s, "%sif (%s) {\n", Tabs_get(tabs), code_is_last); Tabs_increment(tabs);
					fprintf(s, "%sis_last_element_in_array = true;\n", Tabs_get(tabs)); Tabs_decrement(tabs);
					fprintf(s, "%s}\n", Tabs_get(tabs));
					for (int i=attribute->dimension->size-1; i>=0; i--) {
						if (i<attribute->dimension->size-1) {
							fprintf(s, "%sfprintf(%s, \"%%s\", (is_last_element_in_array)?\"\":\"\\n\");\n", Tabs_get(tabs), stream_name);
						}
						Tabs_decrement(tabs);
						fprintf(s, "%s}\n", Tabs_get(tabs));
					}
					{
						string_free(code_loop);
						string_free(code_indexes);
						string_free(code_is_last);
					}
					// fprintf(s, "%s\n", Tabs_get(tabs));
					break;
				}
				case NO_TYPE: {
					fprintf(stderr, "\'generate_to_string_method_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
					exit(1);
				}
			}
			fprintf(s, "%sfprintf(%s, \"%c\");\n", Tabs_get(tabs), stream_name, (attribute->next!=NULL)?';':'.');
		}
		//
		Tabs_decrement(tabs);
		fprintf(s, "%s}\n", Tabs_get(tabs)); Tabs_decrement(tabs);
		fprintf(s, "%s}", Tabs_get(tabs));
		
		{
			fclose(s);
			Tabs_free(tabs);
			string_free(stream_name);
		}
	}
	char *code_structure_to_string;
	{
		size_t code_structure_to_string_length;
		FILE *s = open_memstream(&code_structure_to_string, &code_structure_to_string_length);
		
		Tabs *tabs = Tabs_create();
		
		fprintf(s, "%schar * %s_to_string(void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(s, "%sreturn to_string(Pointer_create(%s, structure));\n", Tabs_get(tabs), structure->name_upper); Tabs_decrement(tabs);
		fprintf(s, "%s}", Tabs_get(tabs));
		{
			fclose(s);
			Tabs_free(tabs);
		}
	}
	char * code = string_appends(code_structure_to_string_process, "\n", code_structure_to_string, NO_MORE_STRINGS);
	{
		string_free(code_structure_to_string_process);
		string_free(code_structure_to_string);
	}
	return code;
	
	
	fprintf(stream, "%sif (%s%s%s!=NULL) {\n", Tabs_get(tabs), (string_equals(structure->name, attribute->data_type))?"pointerDictionary->stage!=0 && ":"", attribute_pointer, indexes); Tabs_increment(tabs);
	fprintf(stream, "%sPointerDictionary_put_by_value(pointerDictionary, Pointer_create(%s, %s%s));\n", Tabs_get(tabs), attribute_name_upper, attribute_pointer, indexes);
	Tabs_decrement(tabs);
	fprintf(stream, "%s}\n", Tabs_get(tabs));
	
*/
/*
// JSON_CODEC
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
*/

/*
// BYTE_CODEC

	void (*array_of_fwrite_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		fwrite_primitive_value, fwrite_string_value, fwrite_structure_value, fwrite_structure_value,
		fwrite_primitive_value, fwrite_string_value, fwrite_structure_value, fwrite_structure_value
	};
	void (*array_of_fread_value[]) (FILE *, Tabs *, Structure *, Attribute *, char *) = { NULL,
		fread_primitive_value, fread_string_value, fread_structure_value, fread_structure_value,
		fread_primitive_value, fread_string_value, fread_structure_value, fread_structure_value
	};
	char *code_byte_encode_process, *code_byte_decode_process;
	{
		size_t code_byte_encode_process_length, code_byte_decode_process_length;
		FILE *e = open_memstream(&code_byte_encode_process, &code_byte_encode_process_length), *d = open_memstream(&code_byte_decode_process, &code_byte_decode_process_length);
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		char *stream_name = string_create("structure_byte_stream");
		// encode
		fprintf(e, "%svoid %s_byte_encode_process(FILE *structure_byte_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(et), structure->name); Tabs_increment(et);
		// decode
		fprintf(d, "%svoid %s_byte_decode_process(FILE *structure_byte_stream, PointerDictionary *pointerDictionary, void *structure) {\n", Tabs_get(dt), structure->name); Tabs_increment(dt);
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
			fprintf(e, "%slong structure_address;\n", Tabs_get(dt));
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
									string_free(stars_first);
									string_free(stars_second);
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
						string_free(code_indexes);
					}
					break;
				}
				case NO_TYPE: {
					fprintf(stderr, "\'generate_byte_codec_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
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
			string_free(stream_name);
		}
	}
	char *code_byte_encode;
	{
		size_t code_byte_encode_length;
		FILE *code_byte_encode_stream = open_memstream(&code_byte_encode, &code_byte_encode_length);
		Tabs *tabs = Tabs_create();
		fprintf(code_byte_encode_stream, "%sData * %s_byte_encode(void *structure) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(code_byte_encode_stream, "%sreturn byte_encode(Pointer_create(%s, structure));\n", Tabs_get(tabs), structure->name_upper); Tabs_decrement(tabs);
		fprintf(code_byte_encode_stream, "%s}", Tabs_get(tabs));
		{
			fclose(code_byte_encode_stream);
			Tabs_free(tabs);
		}
	}
	char *code_byte_decode;
	{
		size_t code_byte_decode_length;
		FILE *code_byte_decode_stream = open_memstream(&code_byte_decode, &code_byte_decode_length);
		Tabs *tabs = Tabs_create();
		fprintf(code_byte_decode_stream, "%svoid * %s_byte_decode(Data *structure_data) {\n", Tabs_get(tabs), structure->name); Tabs_increment(tabs);
		fprintf(
			code_byte_decode_stream,
			"%1$s%2$s *%3$s = (%2$s *)malloc(sizeof(%2$s));\n"
			"%1$smemset(%3$s, 0x00, sizeof(%3$s));\n"
			"%1$sreturn byte_decode(structure_data, Pointer_create(%4$s, %3$s));\n",
			Tabs_get(tabs), structure->name, structure->shortcut, structure->name_upper
		); Tabs_decrement(tabs);
		fprintf(code_byte_decode_stream, "%s}", Tabs_get(tabs));
		{
			fclose(code_byte_decode_stream);
			Tabs_free(tabs);
		}
	}
	char *code = string_appends(
			code_byte_encode_process,
			"\n",
			code_byte_decode_process,
			"\n",
			code_byte_encode,
			"\n",
			code_byte_decode,
			NO_MORE_STRINGS
	);
	{
		string_free(code_byte_encode_process);
		string_free(code_byte_decode_process);
		string_free(code_byte_encode);
		string_free(code_byte_decode);
	}
	return code;
*/
