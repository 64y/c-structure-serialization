#include "includes.h"


void (*methods[][5]) (FILE *structure_string_stream, PointerDictionary *pointerDictionary, void *structure) = %s;


char * to_string(Pointer *pointer) {
	char *structure_string;
	{
		size_t structure_string_length;
		FILE *structure_string_stream = open_memstream(&structure_string, &structure_string_length);
		
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put_by_value(pointerDictionary, pointer);
		PointerNode *curr = pointerDictionary->head;
		methods[curr->value->name][TO_STRING](structure_string_stream, pointerDictionary, curr->value->pointer);
		for (size_t curr_i=1, size=PointerDictionary_size(pointerDictionary); curr_i<size; size=PointerDictionary_size(pointerDictionary)) {
			PointerDictionary_stage_next(pointerDictionary);
			while (curr_i < size) {
				curr = curr->next;
				curr_i = curr_i + 1;
				fprintf(structure_string_stream, "\n |_ ");
				methods[curr->value->name][TO_STRING](structure_string_stream, pointerDictionary, curr->value->pointer);
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
		fprintf(structure_json_stream, "\"%%s@%%lX\": ", STRUCTURE_NAME_STRING[curr->value->name], (long)curr->value->pointer);
		methods[curr->value->name][JSON_ENCODE](structure_json_stream, pointerDictionary, curr->value->pointer);
		for (size_t curr_i=1, size=PointerDictionary_size(pointerDictionary); curr_i<size; size=PointerDictionary_size(pointerDictionary)) {
			PointerDictionary_stage_next(pointerDictionary);
			while (curr_i < size) {
				curr = curr->next;
				curr_i = curr_i + 1;
				if (curr->value->pointer == NULL) {
					continue;
				}
				fprintf(structure_json_stream, ",\n");
				fprintf(structure_json_stream, "\"%%s@%%lX\": ", STRUCTURE_NAME_STRING[curr->value->name], (long)curr->value->pointer);
				methods[curr->value->name][JSON_ENCODE](structure_json_stream, pointerDictionary, curr->value->pointer);
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
			methods[curr->value->name][JSON_DECODE](structure_json_stream, pointerDictionary, curr->value->pointer);
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

Data * bytes_encode(Pointer *pointer) {
	Data *structure_bytes = Data_create_null();
	{
		FILE *structure_bytes_stream = open_memstream((char **)&structure_bytes->bytes, &structure_bytes->bytes_size);
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		PointerDictionary_put_by_value(pointerDictionary, pointer);
		for (PointerNode *curr = pointerDictionary->head; curr!=NULL; curr=curr->next) {
			fwrite((long *)&curr->value->pointer, sizeof(long), 1, structure_bytes_stream);
			methods[curr->value->name][BYTES_ENCODE](structure_bytes_stream, pointerDictionary, curr->value->pointer);
		}
		{
			fflush(structure_bytes_stream);
			fclose(structure_bytes_stream);
			PointerDictionary_free(pointerDictionary);
		}
	}
	return structure_bytes;
}

void * bytes_decode(Data *structure_bytes, Pointer *pointer) {
	void *structure;
	{
		FILE *structure_bytes_stream = fmemopen(structure_bytes->bytes, structure_bytes->bytes_size, "rb");
		PointerDictionary *pointerDictionary = PointerDictionary_create();
		long structure_address, structure_address_current;
		fread(&structure_address, sizeof(long), 1, structure_bytes_stream);
		fseek(structure_bytes_stream, 0, SEEK_SET);
		char *hashCode;
		{
			size_t hashCode_length;
			FILE *hashCode_stream = open_memstream(&hashCode, &hashCode_length);
			fprintf(hashCode_stream, "%%s@%%lX", STRUCTURE_NAME_STRING[pointer->name], structure_address);
			{
				fclose(hashCode_stream);
			}
		}
		PointerDictionary_put_by_key_and_value(pointerDictionary, hashCode, pointer);
		{
			structure_address = 0;
			free(hashCode);
		}
		for (PointerNode *curr = pointerDictionary->head; curr!=NULL; curr=curr->next) {			
			sscanf(curr->key, "%%*[^@]@%%lX", &structure_address);
			fread(&structure_address_current, sizeof(long), 1, structure_bytes_stream);
			if (structure_address!=structure_address_current) {
				fprintf(stderr, "Wrong order of elements in bytes \'%%s\'!=\'%%lX\'!\n", curr->key, structure_address_current);
				exit(1);
			}
			methods[curr->value->name][BYTES_DECODE](structure_bytes_stream, pointerDictionary, curr->value->pointer);
		}
		structure = pointerDictionary->head->value->pointer;
		{
			fclose(structure_bytes_stream);
			PointerDictionary_free(pointerDictionary);
		}
	}
	return structure;
}
