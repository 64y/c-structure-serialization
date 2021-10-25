/** @file
@brief An example of codecs for Parrot structure. */
#ifndef $1_STRING_H
#define $1_STRING_H


#include "structures/parrot.h"
#include "examples/example_template.h"


void * Parrot_generate(void);
void Parrot_free(void *structure);


void example_of_structure_with_string_member(int DO_FLAGS) {
	example(
		"Structure with String Member",
		"./my_lib",
		"Parrot",
		Parrot_generate,
		Parrot_free,
		DO_FLAGS
	);
}


void * Parrot_generate(void) {
	Parrot *parrot = (Parrot *)malloc(sizeof(Parrot));
	parrot->name = (char *)calloc(3+1, sizeof(char));
	strcpy(parrot->name, "Tom");
	parrot->age = 99;
	return parrot;
}

void Parrot_free(void *structure) {
	Parrot *parrot = (Parrot *) structure;
	if (parrot != NULL) {
		if (parrot->name != NULL) {
			free(parrot->name);
			parrot->name = NULL;
		}
		parrot->age = 0;
		free(parrot);
		parrot = NULL;
	}
}

#endif
