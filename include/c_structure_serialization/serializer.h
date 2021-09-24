#ifndef SERIALIZER_H
#define SERIALIZER_H


typedef struct Serializer {
	void *handle;
	char * (*to_string) (void *);
	char * (*json_encode) (void *);
	void * (*json_decode) (char *);
} Serializer;


Serializer * Serializer_create(char *library_path, char *structure_name);
void Serializer_free(Serializer *serializer);

#endif
