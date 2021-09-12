#ifndef SERIALIZE_H
#define SERIALIZE_H


typedef struct Serialize {
	void *handle;
	char * (*to_string) (void *);
	char * (*json_encode) (void *);
	void * (*json_decode) (char *);
} Serialize;

Serialize * Serialize_create(char *name);
void Serialize_free(Serialize *serialize);

#endif
