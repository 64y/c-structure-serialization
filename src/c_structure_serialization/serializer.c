#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "c_structure_serialization/serializer.h"


char * get_serializer_method_name(char *structure_name, char *method_name);


Serializer * Serializer_create(char *library_path, char *structure_name) {
	Serializer *serializer = (Serializer *)malloc(sizeof(Serializer));
	serializer->handle = dlopen(library_path, RTLD_NOW|RTLD_GLOBAL);
	if (!serializer->handle) {
		fprintf(stderr, "\'Serializer_create\' method is not able to open \"%s\" library!\n", library_path);
		exit(1);
	}
	char *method_name_to_string = get_serializer_method_name(structure_name, "to_string");
	*(void **) (&serializer->to_string) = dlsym(serializer->handle, method_name_to_string);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_to_string, library_path);
		exit(1);
	}
	char *method_name_json_encode = get_serializer_method_name(structure_name, "json_encode");
	*(void **) (&serializer->json_encode) = dlsym(serializer->handle, method_name_json_encode);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_json_encode, library_path);
		exit(1);
	}
	char *method_name_json_decode = get_serializer_method_name(structure_name, "json_decode");
	*(void **) (&serializer->json_decode) = dlsym(serializer->handle, method_name_json_decode);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_json_decode, library_path);
		exit(1);
	}
	char *method_name_byte_encode = get_serializer_method_name(structure_name, "byte_encode");
	*(void **) (&serializer->byte_encode) = dlsym(serializer->handle, method_name_byte_encode);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_byte_encode, library_path);
		exit(1);
	}
	char *method_name_byte_decode = get_serializer_method_name(structure_name, "byte_decode");
	*(void **) (&serializer->byte_decode) = dlsym(serializer->handle, method_name_byte_decode);
	if (dlerror()) {
		fprintf(stderr, "\'Serializer_create\' method can\'t load \'%s\' from \"%s\" library!\n", method_name_byte_decode, library_path);
		exit(1);
	}
	{
		free(method_name_to_string);
		free(method_name_json_encode);
		free(method_name_json_decode);
		free(method_name_byte_encode);
		free(method_name_byte_decode);
	}
	return serializer;
}

void Serializer_free(Serializer *serializer) {
	if (serializer!=NULL) {
		if (serializer->handle!=NULL) {
			dlclose(serializer->handle);
			serializer->handle = NULL;
		}
		serializer->to_string = NULL;
		serializer->json_encode = NULL;
		serializer->json_decode = NULL;
		serializer->byte_encode = NULL;
		serializer->byte_decode = NULL;
		free(serializer);
		serializer = NULL;
	}
}

char * get_serializer_method_name(char *structure_name, char *method_name) {
	char *serializer_method_name = (char *)calloc(strlen(structure_name)+1+strlen(method_name)+1, sizeof(char));
	sprintf(serializer_method_name, "%s_%s", structure_name, method_name);
	return serializer_method_name;
}
