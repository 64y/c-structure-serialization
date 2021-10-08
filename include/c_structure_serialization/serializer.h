#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "c_structure_serialization/utils/data.h"


typedef struct Serializer {
	void *handle;
	char * (*to_string) (void *structure);
	char * (*json_encode) (void *structure);
	void * (*json_decode) (char *structure_json);
	Data * (*bytes_encode) (void *structure);
	void * (*bytes_decode) (Data *structure_bytes);
} Serializer;


Serializer * Serializer_create(char *library_path, char *structure_name);
void Serializer_free(Serializer *serializer);

#endif
