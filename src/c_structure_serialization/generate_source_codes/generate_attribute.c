#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "c_structure_serialization/generate_source_codes/generate_attribute.h"


char * generate_attribute_pointer(Structure *structure, Attribute *attribute) {
	char *pointer;
	{
		size_t pointer_length;
		FILE *pointer_stream = open_memstream(&pointer, &pointer_length);
		if (attribute->type==STRUCTURE || attribute->type==STRUCTURE_ARRAY) {
			fprintf(pointer_stream, "&");
		}
		fprintf(pointer_stream, "%s->%s", structure->shortcut, attribute->name);
		fclose(pointer_stream);
	}
	return pointer;
}

char * generate_attribute_with_loop(Structure *structure, Attribute *attribute, Tabs *tabs, Boolean slash_n) {
	char *code_loop_start;
	{
		size_t code_loop_start_length;
		FILE *code_loop_start_stream = open_memstream(&code_loop_start, &code_loop_start_length);
		for (int i=0; i<attribute->dimension->size; i++, Tabs_increment(tabs)) {
			fprintf(
				code_loop_start_stream,
				"%sfor (int i_%d=0; i_%d<%s%s%s; i_%d++) {\n",
				Tabs_get(tabs),
				i,
				i,
				(i<attribute->dimension->static_size) ? "" : structure->shortcut, (i<attribute->dimension->static_size) ? "" : "->", attribute->dimension->dimensions[i],
				i
			);
		}
		fprintf(code_loop_start_stream, "%s", Tabs_get(tabs));
		fclose(code_loop_start_stream);
	}
	char *code_array_indexes;
	{
		size_t code_array_indexes_length;
		FILE *code_array_indexes_stream = open_memstream(&code_array_indexes, &code_array_indexes_length);
		for (int i=0; i<attribute->dimension->size; i++) {							
			fprintf(code_array_indexes_stream, "[i_%d]", i);
		}
		fclose(code_array_indexes_stream);
	}
	char *code_loop_end;
	{
		size_t code_loop_end_length;
		FILE *code_loop_end_stream = open_memstream(&code_loop_end, &code_loop_end_length);
		fprintf(code_loop_end_stream, "\n");
		for (int i=0; i<attribute->dimension->size; i++) {
			Tabs_decrement(tabs);
			fprintf(code_loop_end_stream, "%s}\n", Tabs_get(tabs));
			if (slash_n) {
				fprintf(code_loop_end_stream, "%sfprintf(string_stream, \"\\n\");\n", Tabs_get(tabs));
			}
		}
		fclose(code_loop_end_stream);
	}
	char *code_loop;
	{
		size_t code_loop_length;
		FILE *code_loop_stream = open_memstream(&code_loop, &code_loop_length);
		fprintf(
			code_loop_stream,
			"%%s"
			"%s"
			"%%s%s%%s"
			"%s",
			code_loop_start,
			code_array_indexes,
			code_loop_end
		);
		fclose(code_loop_stream);
	}
	{
		free(code_loop_start);
		free(code_array_indexes);
		free(code_loop_end);
	}
	return code_loop;
}

