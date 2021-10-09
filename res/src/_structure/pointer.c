#include "includes.h"


Pointer * Pointer_create(StructureName name, void *structure) {
	Pointer *pointer = (Pointer *)malloc(sizeof(Pointer));
	pointer->name = name;
	pointer->pointer = structure;
	return pointer;
}

void Pointer_free(Pointer *pointer) {
	if (pointer != NULL) {
		pointer->pointer = NULL;
		free(pointer);
		pointer = NULL;
	}
}

char * Pointer_to_string(Pointer *pointer) {
	char *pointer_string;
	{
		size_t pointer_string_length;
		FILE *pointer_string_stream = open_memstream(&pointer_string, &pointer_string_length);
		fprintf(
			pointer_string_stream,
			"Pointer@%lX\n"
			"name: \'%s\';\n"
			"pointer: \'%s%lX\'.",
			(long)(void *)pointer, STRUCTURE_NAME_STRING[pointer->name], STRUCTURE_NAME_STRING[pointer->name], (long)pointer->pointer
		);
		fclose(pointer_string_stream);
	}
	return pointer_string;
}


char * Pointer_hash_code(Pointer *pointer) {
	char *pointer_hashCode;
	{
		size_t pointer_hashCode_length;
		FILE *pointer_hashCode_stream = open_memstream(&pointer_hashCode, &pointer_hashCode_length);
		fprintf(pointer_hashCode_stream, "%s@%lX", STRUCTURE_NAME_STRING[pointer->name], (long)pointer->pointer);
		fclose(pointer_hashCode_stream);
	}
	return pointer_hashCode;
}
