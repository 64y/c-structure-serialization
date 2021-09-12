#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <stdio.h>

#include "serialization/registrate.h"
#include "serialization/serialize.h"


#include "structures/all_primitives.h"

void example_of_structure_with_primitives_members() {
	puts(" = = = Example of Structure with Primitives Members = = = ");
	
	Serialize_registrate_structure("AllPrimitives", "structures/all_primitives.h");
	Serialize *all_primitives_serialize = Serialize_create("AllPrimitives");
	
	AllPrimitives allPrimitives = {'D', 0xFF, 0x00, 1, 2, 3l, 4.0f, 5.5};
	
	puts("TO_STRING");
	char *allPrimitives_string = all_primitives_serialize->to_string(&allPrimitives);
	puts(allPrimitives_string);
	
	{
		Serialize_free(all_primitives_serialize);
		
		free(allPrimitives_string);
	}
	puts(" = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");
}

#endif
