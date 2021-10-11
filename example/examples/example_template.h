#ifndef EXAMPLE_H
#define EXAMPLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <c_structure_serialization/serializer.h>
#include <c_structure_serialization/utils/data.h>


#define DO_TO_STRING		0b00001
#define DO_JSON_ENCODE	0b00010
#define DO_JSON_DECODE	0b00100
#define DO_BYTE_ENCODE	0b01000
#define DO_BYTE_DECODE	0b10000


void example (
	char *example_name,
	char *library_path,
	char *structure_name,
	void * (*structure_generate) (void),
	void (*structure_free) (void *structure),
	int DO_FLAG
) {
	printf(" = = = Example of %s = = = \n\n", example_name);
	
	Serializer *serializer = Serializer_create(library_path, structure_name);
	
	void *structure = structure_generate();
	
	if (DO_FLAG & DO_TO_STRING) {
		char *structure_string = serializer->to_string(structure);
		printf("TO_STRING:\n%s\n\n", structure_string);
		{
			free(structure_string);
		}
	}
	if (DO_FLAG & DO_JSON_ENCODE) {
		char *structure_json = serializer->json_encode(structure);
		printf("JSON_ENCODE:\n%s\n\n", structure_json);
		{
			free(structure_json);
		}
	}
	if (DO_FLAG & DO_JSON_DECODE) {
		char *structure_json = serializer->json_encode(structure);
		void *structure_temp = serializer->json_decode(structure_json);
		char *structure_temp_string = serializer->to_string(structure_temp);
		printf("JSON_DECODE:\n%s\n\n", structure_temp_string);
		free(structure_json);
		structure_free(structure_temp);
		free(structure_temp_string);
	}
	if (DO_FLAG & DO_BYTE_ENCODE) {
		Data *structure_data = serializer->byte_encode(structure);
		char *structure_data_string = Data_to_string(structure_data);
		printf("BYTES_ENCODE:\n%s\n\n", structure_data_string);
		{
			Data_free(structure_data);
			free(structure_data_string);
		}
	}
	if (DO_FLAG & DO_BYTE_ENCODE) {
		Data *structure_data = serializer->byte_encode(structure);
		void *structure_temp = serializer->byte_decode(structure_data);
		char *structure_temp_string = serializer->to_string(structure_temp);
		printf("BYTES_DECODE:\n%s\n\n", structure_temp_string);
		{
			Data_free(structure_data);
			structure_free(structure_temp);
			free(structure_temp_string);
		}
	}
	{
		structure_free(structure);
		Serializer_free(serializer);
	}
	printf(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n\n");
}

#endif
