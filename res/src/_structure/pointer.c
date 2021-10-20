#include "includes.h"


Pointer * Pointer_create_by_name_pointer(StructureName name, void *structure) {
	return Pointer_create_by_name_pointer_address(name, structure, (long) structure);
}

Pointer * Pointer_create_by_name_pointer_address(StructureName name, void *structure, long address) {
	Pointer *pointer = (Pointer *)malloc(sizeof(Pointer));
	pointer->name = name;
	pointer->pointer = structure;
	pointer->address = address;
	pointer->address_id = 0;
	pointer->hashCode = NULL;
	{
		size_t hashCode_length;
		FILE *hashCode_stream = open_memstream(&pointer->hashCode, &hashCode_length);
		fprintf(hashCode_stream, "%s@%lX", STRUCTURE_NAME_STRING[pointer->name], pointer->address);
		{
			fclose(hashCode_stream);
		}
	}
	pointer->next = NULL;
	return pointer;
}

Pointer * Pointer_create_by_name_pointer_hashCode(StructureName name, void *structure, char *hashCode) {
	Pointer *pointer = (Pointer *)malloc(sizeof(Pointer));
	pointer->name = name;
	pointer->pointer = structure;
	pointer->address = 0;
	pointer->address_id = 0;
	sscanf(hashCode, "%[^@]@%lX", &pointer->address);
	pointer->hashCode = (char *)calloc(strlen(hashCode)+1, sizeof(char));
	strcpy(pointer->hashCode, hashCode);
	pointer->next = NULL;
	return pointer;
}

void Pointer_free(Pointer *pointer) {
	if (pointer!=NULL) {
		if (pointer->name!=NULL) {
			free(pointer->name);
			pointer->name = NULL;
		}
		pointer->address = 0;
		pointer->address_id = 0;
		if (pointer->hashCode!=NULL) {
			free(pointer->hashCode);
			pointer->hashCode = NULL;
		}
		pointer->next = NULL;
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
			"pointer: \'%lX\';"
			"address: \'%lX\';"
			"address_id: \'%X\';"
			"hashCode: \'%s\';"
			"next: \'%lX\'.",
			(long)(void *)pointer, STRUCTURE_NAME_STRING[pointer->name], (long)pointer->pointer, pointer->address, pointer->address_id, pointer->hashCode, (long)pointer->next
		);
		fclose(pointer_string_stream);
	}
	return pointer_string;
}
