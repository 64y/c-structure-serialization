/** @file
@brief An example of codecs for AllPrimitives structure. */
#ifndef $0_PRIMITIVES_H
#define $0_PRIMITIVES_H


#include "structures/all_primitives.h"
#include "examples/example_template.h"


void * AllPrimitives_generate(void);
void AllPrimitives_free(void *structure);


void example_of_structure_with_primitives_members(int DO_FLAGS) {
	example(
		"Structure with Primitives Members",
		"./my_lib",
		"AllPrimitives",
		AllPrimitives_generate,
		AllPrimitives_free,
		DO_FLAGS
	);
}


void * AllPrimitives_generate(void) {
	AllPrimitives *allPrimitives = (AllPrimitives *)malloc(sizeof(AllPrimitives));
	allPrimitives->c = 'D';
	allPrimitives->uc = 0xFF;
	allPrimitives->b = 0x00;
	allPrimitives->s = 1;
	allPrimitives->i = 2;
	allPrimitives->l = 3l;
	allPrimitives->f = 4.2f;
	allPrimitives->d = 5.8;
	return allPrimitives;
}

void AllPrimitives_free(void *structure) {
	AllPrimitives *allPrimitives = (AllPrimitives *) structure;
	if (allPrimitives != NULL) {
		free(allPrimitives);
		allPrimitives = NULL;
	}
}

#endif
