#include "includes.h"


void (*to_string_process_methods[]) (FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure) = {
	%s
};

void (*json_encode_process_methods[]) (FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure) = {
	%s
};

void (*json_decode_process_methods[]) (FILE *structure_json_stream, PointerDictionary *pointerDictionary, void *structure) = {
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
		to_string_process_methods[curr->value->name](structure_string_stream, pointerDictionary, curr->value->pointer);
		for (size_t curr_i=1, size=PointerDictionary_size(pointerDictionary); curr_i<size; size=PointerDictionary_size(pointerDictionary)) {
			PointerDictionary_stage_next(pointerDictionary);
			while (curr_i < size) {
				curr = curr->next;
				curr_i = curr_i + 1;
				fprintf(structure_string_stream, "\n |_ ");
				to_string_process_methods[curr->value->name](structure_string_stream, pointerDictionary, curr->value->pointer);
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
		fprintf(structure_json_stream, "\"%%s@%%lx\": ", STRUCTURE_NAME_STRING[curr->value->name], (long)curr->value->pointer);
		json_encode_process_methods[curr->value->name](structure_json_stream, pointerDictionary, curr->value->pointer);
		for (size_t curr_i=1, size=PointerDictionary_size(pointerDictionary); curr_i<size; size=PointerDictionary_size(pointerDictionary)) {
			PointerDictionary_stage_next(pointerDictionary);
			while (curr_i < size) {
				curr = curr->next;
				curr_i = curr_i + 1;
				if (curr->value->pointer == NULL) {
					continue;
				}
				fprintf(structure_json_stream, ",\n");
				fprintf(structure_json_stream, "\"%%s@%%lx\": ", STRUCTURE_NAME_STRING[curr->value->name], (long)curr->value->pointer);
				json_encode_process_methods[curr->value->name](structure_json_stream, pointerDictionary, curr->value->pointer);
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
		size_t structure_json_length = strlen(structure_json);
		FILE *structure_json_stream = fmemopen(structure_json, structure_json_length, "r");
		
		char *hashCode;
		size_t hashCode_length;
		sscanf(structure_json+1, "%%*[$0-9@A-Z_a-z]%%ln", &hashCode_length);
		hashCode = (char *)calloc(hashCode_length + 1, sizeof(char));
		sscanf(structure_json, "\"%%[$0-9@A-Z_a-z]\": ", hashCode);
		
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, pointer);
		{
			free(hashCode);
			hashCode_length = 0;
		}
		for (PointerNode *curr=pointerDictionary->head; curr!=NULL; curr=curr->next) {
			fscanf(structure_json_stream, ",\n");
			{	
				fscanf(structure_json_stream, "\"");
				fscanf(structure_json_stream, "%%*[$0-9@A-Z_a-z]%%ln", &hashCode_length);
				fseek(structure_json_stream, -hashCode_length, SEEK_CUR);
				hashCode = (char *)calloc(hashCode_length + 1, sizeof(char));
				fscanf(structure_json_stream, "%%[$0-9@A-Z_a-z]", hashCode);
				fscanf(structure_json_stream, "\": ");
			}
			if (strcmp(curr->key, hashCode)!=0) {
				fprintf(stderr, "Wrong order of elements in json \'%%s\'!=\'%%s\'!\n", curr->key, hashCode);
				exit(1);
			}
			json_decode_process_methods[curr->value->name](structure_json_stream, pointerDictionary, curr->value->pointer);
			{
				free(hashCode);
				hashCode_length = 0;
			}
		}
		structure = pointerDictionary->head->value->pointer;
		{
			fclose(structure_json_stream);
			PointerDictionary_free(pointerDictionary);
		}
	}
	return structure;
}
