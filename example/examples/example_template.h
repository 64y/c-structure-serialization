/** @file
@brief A definition and declaration of example template method. */
#ifndef EXAMPLE_H
#define EXAMPLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <c_structure_serialization/serializer.h>
#include <c_structure_serialization/utils/data.h>


#define DO_TO_STRING		0b00001 ///< DO_FLAG for to_string
#define DO_JSON_ENCODE	0b00010 ///< DO_FLAG for json_encode
#define DO_JSON_DECODE	0b00100 ///< DO_FLAG for json_decode
#define DO_BYTE_ENCODE	0b01000 ///< DO_FLAG for byte_encode
#define DO_BYTE_DECODE	0b10000 ///< DO_FLAG for byte_decode


/** @brief A template example method.
@details Method create a Serializer for Structure structure_name by loading codecs from file with path library_path. Method demostrates the codec performance for each codec if DO_FLAG variable. Method uses structure_generate and structure_free methods to create and to free an instance of Structure with name structure_name.
@param example_name Example message string;
@param library_path The path of library file;
@param structure_name The name of Structure;
@param structure_generate A pointer to method to create an instance of Structure;
@param structure_free A pointer to method to free allocated memory for an instance of Structure;
@param DO_FLAG Actions to be performed upon generated Structure. */
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
