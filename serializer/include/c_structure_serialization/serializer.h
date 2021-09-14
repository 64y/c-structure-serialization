#ifndef SERIALIZER_H
#define SERIALIZER_H


#define LIBRARY_NAME "libcstructureserialization"


typedef struct Serializer {
	void *handle;
	char * (*to_string) (void *);
	char * (*json_encode) (void *);
	void * (*json_decode) (char *);
} Serializer;


Serializer * Serializer_create(char *structure_name);
void Serializer_free(Serializer *serializer);

#endif
