#include <string.h>

#include "utils/basic_defines.h"
#include "utils/array_of.h"


void * array_string_create(void *element) {
	return string_copy((char *) element);
}

char * array_string_to_string(void *element) {
	return string_copy((char *) element);
}

void array_string_free(void *element) {
	free((char *)element);
}

Array * Array_of_string_create() {
	return Array_create(array_string_create, array_string_to_string, array_string_free);
}

int array_string_cmp(const void *a, const void *b) {
	return strcmp(*(char **) a, *(char **) b);
}


void * array_Structure_arguments(char *file_path, Array *source_code) {
	void **args = (void **)calloc(2, sizeof(void *));
	args[0] = file_path;
	args[1] = source_code;
	return args;
}

void * array_Structure_create(void *element) {
	void **args = (void **) element;
	Structure *structure = Structure_create_by_file_path_and_source_code((char *)args[0], (Array *) args[1]);
	free(args);
	return structure;
}

char * array_Structure_to_string(void *element) {
	return Structure_to_string((Structure *) element);
}

void array_Structure_free(void *element) {
	Structure_free((Structure *) element);
}

Array * Array_of_Structure_create() {
	return Array_create(array_Structure_create, array_Structure_to_string, array_Structure_free);
}

