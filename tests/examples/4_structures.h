#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>

#include <c_structure_serialization/serializer.h>


#include "structures/pets.h"

void example_of_structure_with_structures_and_structures_pointers() {
	puts(" = = = Example of Structure with Structures and Structures Pointers = = = ");
	
	Serializer *pets_serializer = Serializer_create("Pets");
	
	Pets *pets;
	{
		pets = Pets_create();
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
	}
		
	puts("TO_STRING:");
	char *pets_string = pets_serializer->to_string(pets);
	puts(pets_string);
	
	{
		Serializer_free(pets_serializer);
		
		Pets_free(pets);
		
		free(pets_string);
	}
}

#endif
