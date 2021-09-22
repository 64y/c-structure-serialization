#include <stddef.h>
#include <stdio.h>

#include "c_structure_serialization/generate_source_codes/generate_json_codec.h"


char * generate_json_encode_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_json_encode(void *pointer);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * generate_json_encode_definition(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "char * %s_json_encode(void *pointer) {\n", structure->name);
		fprintf(code_stream, "\treturn NULL;\n");
		fprintf(code_stream, "}");
		fclose(code_stream);
	}
	return code;
}

char * generate_json_decode_declaration(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void * %s_json_decode(char *json);", structure->name);
		fclose(code_stream);
	}
	return code;
}

char * generate_json_decode_definition(Structure *structure) {
	char *code;
	{
		size_t code_length;
		FILE *code_stream = open_memstream(&code, &code_length);
		fprintf(code_stream, "void * %s_json_decode(char *json) {\n", structure->name);
		fprintf(code_stream, "\treturn NULL;\n");
		fprintf(code_stream, "}");
		fclose(code_stream);
	}
	return code;
}
