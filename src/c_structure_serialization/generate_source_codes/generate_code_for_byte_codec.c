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
#include "c_structure_serialization/generate_source_codes/generate_code_for_byte_codec.h"


void generate_byte_codec_declaration(FILE *h_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		h_stream,
		"%1$sData * %2$s_byte_encode(void *structure);\n"
		"%1$svoid * %2$s_byte_decode(Data *structure_data);\n"
		"%1$svoid %2$s_byte_encode_process(FILE *structure_byte_stream, PointerSet *pointerSet, Pointer *pointer);\n"
		"%1$svoid %2$s_byte_decode_process(FILE *structure_byte_stream, PointerSet *pointerSet, Pointer *pointer);",
		Tabs_get(tabs), structure->name
	);
}

void generate_byte_codec_definition(FILE *c_stream, Tabs *tabs, Structure *structure) {
	fprintf(
		c_stream,
		"%1$sData * %3$s_byte_encode(void *structure) {\n"
		"%1$s%2$sData *data = encode(BYTE_ENCODE, Pointer_create_by_name_pointer(%4$s, structure));\n"
		"%1$s%2$sreturn data;\n"
		"%1$s}\n"
		"%1$s\n"
		"%1$svoid * %3$s_byte_decode(Data *structure_byte) {\n"
		"%1$s%2$s%3$s *%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$slong structure_address = 0;\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sFILE *structure_byte_stream = fmemopen(structure_byte->bytes, structure_byte->bytes_size, \"rb\");\n"
		"%1$s%2$s%2$sstructure_address = fread_uint32_value30bit_size2bit(structure_byte_stream);\n"
		"%1$s%2$s%2$s{\n"
		"%1$s%2$s%2$s%2$sfclose(structure_byte_stream);\n"
		"%1$s%2$s%2$s}\n"
		"%1$s%2$s}\n"
		"%1$s%2$svoid *structure = decode(\n"
		"%1$s%2$s%2$sBYTE_DECODE,\n"
		"%1$s%2$s%2$sPointer_create_by_name_pointer_address(%4$s, %5$s, structure_address),\n"
		"%1$s%2$s%2$sstructure_byte\n"
		"%1$s%2$s);\n"
		"%1$s%2$sreturn structure;\n"
		"%1$s}",
		Tabs_get(tabs), Tabs_get_tab(tabs), structure->name, structure->name_upper, structure->shortcut
	);
	// BYTE_CODEC
	void (*byte_encode_methods[]) (FILE *, Tabs *, Attribute *, char *) = { NULL,
		byte_encode_primitive, byte_encode_string, byte_encode_structure, byte_encode_structure,
		byte_encode_primitive, byte_encode_string, byte_encode_structure, byte_encode_structure
	};
	void (*byte_decode_methods[]) (FILE *, Tabs *, Attribute *, char *) = { NULL,
		byte_decode_primitive, byte_decode_string, byte_decode_structure, byte_decode_structure_pointer,
		byte_decode_primitive, byte_decode_string, byte_decode_structure, byte_decode_structure_pointer
	};
	char *code_byte_encode_process, *code_byte_decode_process;
	{
		size_t code_byte_encode_process_length, code_byte_decode_process_length;
		FILE *e = open_memstream(&code_byte_encode_process, &code_byte_encode_process_length), *d = open_memstream(&code_byte_decode_process, &code_byte_decode_process_length);
		Tabs *et = Tabs_create(), *dt = Tabs_create();
		// encode
		fprintf(e, "%svoid %s_byte_encode_process(FILE *structure_byte_stream, PointerSet *pointerSet, Pointer *pointer) {\n", Tabs_get(et), structure->name); Tabs_increment(et);
		// decode
		fprintf(d, "%svoid %s_byte_decode_process(FILE *structure_byte_stream, PointerSet *pointerSet, Pointer *pointer) {\n", Tabs_get(dt), structure->name); Tabs_increment(dt);
		if (Structure_contains_string_attributes(structure)) {
			//encode
			fprintf(e, "%ssize_t string_length;\n", Tabs_get(dt));
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
			fprintf(
				e,
				"%1$sPointer *structure_pointer;\n"
				"%1$schar *structure_hashCode;\n"
				"%1$ssize_t structure_hashCode_length;\n"
				"%1$sFILE *structure_hashCode_stream;\n"
				"%1$slong structure_address;\n",
				Tabs_get(et)
			);
			//decode
			fprintf(
				d,
				"%1$schar *structure_hashCode;\n"
				"%1$ssize_t structure_hashCode_length;\n"
				"%1$sFILE *structure_hashCode_stream;\n"
				"%1$slong structure_address;\n",
				Tabs_get(dt)
			);
		}
		// encode
		fprintf(e, "%1$s%2$s *%3$s = (%2$s *) pointer->pointer;\n", Tabs_get(et), structure->name, structure->shortcut);
		// decode
		fprintf(d, "%1$s%2$s *%3$s = (%2$s *) pointer->pointer;\n", Tabs_get(dt), structure->name, structure->shortcut);
		for (Attribute *attribute=structure->head; attribute!=NULL; attribute=attribute->next) {
			void (*byte_encode_method) (FILE *, Tabs *, Attribute *, char *) = byte_encode_methods[attribute->type];
			void (*byte_decode_method) (FILE *, Tabs *, Attribute *, char *) = byte_decode_methods[attribute->type];
			switch (attribute->type) {
				case PRIMITIVE: case STRING: case STRUCTURE: case STRUCTURE_POINTER: {
					char *attribute_pointer = generate_attribute_pointer(structure, attribute, NULL);
					// encode
					byte_encode_method(e, et, attribute, attribute_pointer);
					// decode
					byte_decode_method(d, dt, attribute, attribute_pointer);
					{
						string_free(attribute_pointer);
					}
					break;
				}
				case PRIMITIVE_ARRAY: case STRING_ARRAY: case STRUCTURE_ARRAY: case STRUCTURE_POINTER_ARRAY: {
					int number_of_stars = attribute->dimension->dynamic_size_source + (attribute->type==STRUCTURE_POINTER_ARRAY);
					char *attribute_pointer, *code_indexes;
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
					attribute_pointer = generate_attribute_pointer(structure, attribute, code_indexes);
					// encode
					byte_encode_method(e, et, attribute, attribute_pointer);
					// decode
					byte_decode_method(d, dt, attribute, attribute_pointer);
					
					for (int i=0; i<attribute->dimension->size; i++) {
						// encode
						Tabs_decrement(et);
						fprintf(e, "%s}\n", Tabs_get(et));
						// decode
						Tabs_decrement(dt);
						fprintf(d, "%s}\n", Tabs_get(dt));
					}
					{
						string_free(attribute_pointer);
						string_free(code_indexes);
					}
					break;
				}
				case NO_TYPE: {
					fprintf(stderr, "\'generate_byte_codec_definition\' is not allowed to work with \'%s\' attribute type!\n", ATTRIBUTE_TYPE_STRING[attribute->type]);
					exit(1);
				}
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
		}
	}
	fprintf(c_stream, "\n%s\n\n%s", code_byte_encode_process, code_byte_decode_process);
	{
		string_free(code_byte_encode_process);
		string_free(code_byte_decode_process);
	}

}


void byte_encode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfwrite(&%s, sizeof(%s), 1, structure_byte_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute->data_type
	);
}

void byte_encode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer){
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

void byte_encode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$s{\n"
		"%1$s%2$sstructure_hashCode_stream = open_memstream(&structure_hashCode, &structure_hashCode_length);\n"
		"%1$s%2$sfprintf(structure_hashCode_stream, \"%%s@%%lX\", \"%3$s\", (long)(void *)%4$s);\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sfclose(structure_hashCode_stream);\n"
		"%1$s%2$s}\n"
		"%1$s}\n"
		"%1$sstructure_pointer = PointerSet_get_by_hashCode(pointerSet, structure_hashCode);\n"
		"%1$sfwrite_uint32_value30bit_size2bit(structure_byte_stream, structure_pointer->address_id);\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type, attribute_pointer
	);
	if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
		fprintf(stream, "%sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%s, %s));\n", Tabs_get(tabs), attribute->data_type_upper, attribute_pointer);
	} else {
		fprintf(stream, "%1$sif (%4$s!=NULL) {\n%1$s%2$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer(%3$s, %4$s));\n%1$s}\n", Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer);
	}
}

void byte_decode_primitive(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfread(&%s, sizeof(%s), 1, structure_byte_stream);\n",
		Tabs_get(tabs), attribute_pointer, attribute->data_type
	);
}

void byte_decode_string(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%sfread(&string_length, sizeof(size_t), 1, structure_byte_stream);\n",
		Tabs_get(tabs)
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
			"%1$s%2$sstrcpy(%3$s, string);\n"
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

void byte_decode_structure(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sstructure_address = fread_uint32_value30bit_size2bit(structure_byte_stream);\n"
		"%1$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer_address(%3$s, %4$s, structure_address));\n"
		"%1$s{\n"
		"%1$s%2$sstructure_address = 0;\n"
		"%1$s}\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type_upper, attribute_pointer
	);
}

void byte_decode_structure_pointer(FILE *stream, Tabs *tabs, Attribute *attribute, char *attribute_pointer) {
	fprintf(
		stream,
		"%1$sstructure_address = fread_uint32_value30bit_size2bit(structure_byte_stream);\n"
		"%1$sif (structure_address!=0) {\n"
		"%1$s%2$sstructure_hashCode_stream = open_memstream(&structure_hashCode, &structure_hashCode_length);\n"
		"%1$s%2$sfprintf(structure_hashCode_stream, \"%%s@%%lX\", \"%3$s\", structure_address);\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sfclose(structure_hashCode_stream);\n"
		"%1$s%2$s}\n"
		"%1$s%2$sif (PointerSet_contains_by_hashCode(pointerSet, structure_hashCode)) {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *) PointerSet_get_by_hashCode(pointerSet, structure_hashCode);\n"
		"%1$s%2$s} else {\n"
		"%1$s%2$s%2$s%5$s = (%3$s *)malloc(sizeof(%3$s));\n"
		"%1$s%2$s%2$smemset(%5$s, 0x00, sizeof(%3$s));\n"
		"%1$s%2$s%2$sPointerSet_add(pointerSet, Pointer_create_by_name_pointer_hashCode(%4$s, %5$s, structure_hashCode));\n"
		"%1$s%2$s}\n"
		"%1$s%2$s{\n"
		"%1$s%2$s%2$sstructure_address = 0;\n"
		"%1$s%2$s%2$sfree(structure_hashCode);\n"
		"%1$s%2$s%2$sstructure_hashCode = NULL;\n"
		"%1$s%2$s%2$sstructure_hashCode_length = 0;\n"
		"%1$s%2$s}\n"
		"%1$s} else {\n"
		"%1$s%2$s%5$s = NULL;\n"
		"%1$s}\n"
		"%1$s%2$s\n",
		Tabs_get(tabs), Tabs_get_tab(tabs), attribute->data_type, attribute->data_type_upper, attribute_pointer
	);
}
