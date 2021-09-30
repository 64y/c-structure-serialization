#include "includes.h"


char * (*to_string_process_methods[]) (PointerDictionary *pointerDictionary, void *structure) = {
	%s
};

char * (*json_encode_methods[]) (PointerDictionary *pointerDictionary, void *structure) = {
	%s
};

void * (*json_decode_methods[]) (PointerDictionary *pointerDictionary, char *structure_json, void *structure) = {
	%s
};


char * to_string(Pointer *pointer) {
	char *structure_string;
	{
		size_t structure_string_length;
		FILE *structure_string_stream = open_memstream(&structure_string, &structure_string_length);
		
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put(pointerDictionary, pointer);
		PointerNode *curr = pointerDictionary->head;
		char *curr_string = to_string_process_methods[curr->value->name](pointerDictionary, curr->value->pointer);
		fprintf(structure_string_stream, "%%s", curr_string);
		{
			free(curr_string);
		}
		for (size_t curr_i=1, size=PointerDictionary_size(pointerDictionary); curr_i<size; size=PointerDictionary_size(pointerDictionary)) {
			PointerDictionary_stage_next(pointerDictionary);
			while (curr_i < size) {
				curr = curr->next;
				curr_i = curr_i + 1;
				curr_string = to_string_process_methods[curr->value->name](pointerDictionary, curr->value->pointer);
				fprintf(structure_string_stream, "\n |_ %%s", curr_string);
				{
					free(curr_string);
				}
			}
		}
		{
			fclose(structure_string_stream);
			PointerDictionary_free(pointerDictionary);
		}
	}
	return structure_string;
}

char * json_encode(Pointer *pointer) {
	return NULL;
}

void * json_decode(char *pointer_json, Pointer *pointer) {
 	return NULL;
}
