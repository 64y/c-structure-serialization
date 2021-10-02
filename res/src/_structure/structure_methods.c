#include "includes.h"


char * (*to_string_process_methods[]) (PointerDictionary *pointerDictionary, void *structure) = {
	%s
};

char * (*json_encode_process_methods[]) (PointerDictionary *pointerDictionary, void *structure) = {
	%s
};

void (*json_decode_process_methods[]) (PointerDictionary *pointerDictionary, FILE *structure_json_stream, void *structure) = {
	%s
};


char * to_string(Pointer *pointer) {
	char *structure_string;
	{
		size_t structure_string_length;
		FILE *structure_string_stream = open_memstream(&structure_string, &structure_string_length);
		
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put_by_value(pointerDictionary, pointer);
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

	char *structure_json;
	{
		size_t structure_json_length;
		FILE *structure_json_stream = open_memstream(&structure_json, &structure_json_length);
		
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put_by_value(pointerDictionary, pointer);
		PointerNode *curr = pointerDictionary->head;
		char *curr_json = json_encode_process_methods[curr->value->name](pointerDictionary, curr->value->pointer);
		fprintf(structure_json_stream, "\"%%s@%%lx\": %%s", STRUCTURE_NAME_STRING[curr->value->name], (long)curr->value->pointer, curr_json);
		{
			free(curr_json);
		}
		for (size_t curr_i=1, size=PointerDictionary_size(pointerDictionary); curr_i<size; size=PointerDictionary_size(pointerDictionary)) {
			PointerDictionary_stage_next(pointerDictionary);
			while (curr_i < size) {
				curr = curr->next;
				curr_i = curr_i + 1;
				/*if (curr->value->pointer!= NULL) {
					continue;
				}*/
				curr_json = json_encode_process_methods[curr->value->name](pointerDictionary, curr->value->pointer);
				fprintf(structure_json_stream, ",\n");
				fprintf(structure_json_stream, "\"%%s@%%lx\": %%s", STRUCTURE_NAME_STRING[curr->value->name], (long)curr->value->pointer, curr_json);
				{
					free(curr_json);
				}
			}
		}
		{
			fclose(structure_json_stream);
			PointerDictionary_free(pointerDictionary);
		}
	}
	return structure_json;
}

void * json_decode(char *structure_json, Pointer *pointer) {
	void *structure;
	{
		char *hashCode = (char *)calloc(1024+1, sizeof(char));
		sscanf(structure_json, "\"%[A-Za-z0-9$_@]\": ", hashCode);
		
		size_t structure_json_length = strlen(structure_json);
		FILE *structure_json_stream = fmemopen(structure_json, structure_json_length, "r");
		
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, pointer);
		
		for (PointerNode *curr=pointerDictionary->head; curr!=NULL; curr=curr->next) {
			memset(hashCode, 0x00, 1024);
			fscanf(structure_json_stream, ",\n");
			fscanf(structure_json_stream, "\"%[A-Za-z0-9$_@]\": ", hashCode);
			if (strcmp(curr->key, hashCode)!=0) {
				fprintf(stderr, "Wrong order of elements in json \'%%s\'!=\'%%s\'!\n", curr->key, hashCode);
				exit(1);
			}
			json_decode_process_methods[curr->value->name](pointerDictionary, structure_json_stream, curr->value->pointer);
		}
		structure = pointerDictionary->head->value->pointer;
		{
			free(hashCode);
			fclose(structure_json_stream);
			PointerDictionary_free(pointerDictionary);
		}
	}
	return structure;
}
