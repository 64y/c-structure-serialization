#ifndef $4_STRUCTURES_H
#define $4_STRUCTURES_H


#include "structures/pets.h"
#include "examples/example_template.h"


void * Pets_generate(void);
void Pets_free_generated(void *structure);


void example_of_structure_with_structures_and_structures_pointers () {
	example(
		"Structure with Structures and Structures Pointers",
		"./my_lib",
		"Pets",
		Pets_generate,
		Pets_free_generated,
		DO_TO_STRING | DO_JSON_ENCODE | DO_JSON_DECODE
	);
}


void * Pets_generate(void) {
	Pets *pets = Pets_create();
	Cat *c0 = Cat_create(10, "Sam", 0.5);
	Cat *c1 = Cat_create(11, "Tom", 0.6);
	Cat *c2 = Cat_create(9, "Vid", 0.9);
	Cat *c3 = Cat_create(7, "Zip", 0.8);
	Cat *c4 = Cat_create(15, "Zap", 0.2);
	Dog *d0 = Dog_create(5, "Rain", "red");
	Dog *d1 = Dog_create(7, "Blizzard", "white");
	Dog *d2 = Dog_create(3, "Thunder", "blue");
	Pets_add_Cat(pets, c0);
	Pets_add_Cat(pets, c1);
	Pets_add_Cat(pets, c2);
	Pets_add_Cat(pets, c3);
	Pets_add_Cat(pets, c4);
	Pets_add_Dog(pets, d0);
	Pets_add_Dog(pets, d1);
	Pets_add_Dog(pets, d2);
	return pets;
}

void Pets_free_generated(void *structure) {
	Pets *pets = (Pets *) structure;
	if (pets != NULL) {
		Pets_free(pets);
		pets = NULL;
	}
}

#endif
